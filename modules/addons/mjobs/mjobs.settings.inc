<?php
function mjobssettings_form()
{
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
				'#name'=>'save',
			),
			'updlinks'=>array(
				'#type'=>'submit',
				'#value'=>'перестроить ссылки',
				'#name'=>'rebuildlinks',
			),
		),
	);
	$fd=variable_get('mjobs srttings',array());
	$form['format']=array(
		'#type'=>'textfield',
		'#title'=>'Формат строки заголовка',
		'#default_value'=>empty($fd['format'])?'':$fd['format'],
		'#required'=>true,
		'#description'=>'[title] - заголовок ноды, [city] - населённый пункт',
	);
	$form['cities']=array(
		'#type'=>'textarea',
		'#title'=>'Города',
		'#resizable'=>false,
		'#required'=>true,
		'#default_value'=>empty($fd['cities'])?'':implode("\n",$fd['cities']),
	);
	// достать страницы .. 
	$res=db_select('node','n');
	$res->condition('n.type','page');
	$res->condition('n.status',1);
	$res->fields('n',array('nid','title'));
	$nids=$res->execute()->fetchAllKeyed();
	$form['nids']=array(
		'#title'=>'Источник заголовков',
		'#type'=>'select',
		'#options'=>$nids,
		'#required'=>true,
		'#default_value'=>empty($fd['nids'])?array():$fd['nids'],
		'#multiple'=>true,
		'#size'=>20,
	);
	//drupal_uninstall_schema('mjobs');
	//drupal_install_schema('mjobs');
	return $form;
}
// ===========================================
function mjobssettings_form_submit($form,$form_state)
{
	form_state_values_clean($form_state);
	$vals=$form_state['values'];
	$vals['cities']=array_map('trim',preg_split('#\r\n#imsu',$vals['cities'],-1,PREG_SPLIT_NO_EMPTY));
	variable_set('mjobs srttings',$vals);
	drupal_set_message('Настройки сохранены');
	if ($form_state['triggering_element']['#name']=='rebuildlinks')
	{
		// удалить то что было 
		$res=db_delete('jobslinks');
		$res->execute();
		// загрузить заголовки.. 
		$res=db_select('node','n');
		$res->condition('n.nid',$vals['nids']);
		$res->fields('n',array('nid','title'));
		$nids=$res->execute()->fetchAllKeyed();
		/// добавляем записи . 
		$res=db_insert('jobslinks');
		$res->fields(array('path','city','nid'));
		foreach($nids as $n=>$t)
			foreach($vals['cities'] as $c)
			{
				$t=preg_replace('# +#',' ',trim($t));
				$c=preg_replace('# +#',' ',trim($c));
				$path=str_replace(array('[title]','[city]'),array($t,$c),$vals['format']);
				$path=preg_replace('#-+#','-',strtolower(str_replace('_','-',transliteration_clean_filename($path))));

				$res->values(array(
					$path,$c,$n
				));
			}
		$res->execute();
		drupal_set_message('Ссылки перестроены.');
	}
}
?>