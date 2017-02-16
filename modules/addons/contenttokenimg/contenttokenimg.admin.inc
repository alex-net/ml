<?php 
function galls_config_form($form,$form_state)
{
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
			),
		),
	);
	$nt=array();
	$fd=variable_get('context-token-imgs-data',array());
	$fd=empty($fd['gp'])?array():$fd['gp'];

	if (!empty($form_state['values']))
	{
		form_state_values_clean($form_state);
		$te=$form_state['triggering_element'];
		if ($te['#name']=='gall-is')
			$fd=$form_state['values'];
	}
	
	foreach(node_type_get_types() as $v)
		$nt[$v->type]=$v->name;
	// остать и выбрать .. типы нод .. 
	$form['gall-is']=array(
		'#type'=>'select',
		'#title'=>'Тип материала галереи',
		'#options'=>$nt,
		'#empty_option'=>'Не выбрано',
		'#required'=>true,
		'#default_value'=>empty($fd['gall-is'])?'':$fd['gall-is'],
		'#ajax'=>array(
			'callback'=>'galls_config_form_cbjs',
		),
	);

	$fimgs=$fcats=array();
	$ft=field_info_fields();
	
	
	if(!empty($fd['gall-is']))
	foreach(field_info_instances('node',$fd['gall-is']) as $v)
		switch($ft[$v['field_name']]['type'])
		{
			case 'image':
				$fimgs[$v['field_name']]=$v['label'];
			break;
			case 'taxonomy_term_reference':
				$fcats[$v['field_name']]=$v['label'];
			
		}
	
		
	$form['gallparams']=array(
		'#type'=>'container',
		'#attributes'=>array(
			'class'=>array('gallparams-wrapper'),
		),
		'imagefield'=>array(
			'#type'=>'select',
			'#title'=>'Поле картинок',
			'#options'=>$fimgs,
			'#empty_option'=>'не выбрано',
			'#required'=>true,
			'#default_value'=>empty($fd['imagefield'])?'':$fd['imagefield'],
		),
		'termfield'=>array(
			'#type'=>'select',
			'#title'=>'Поле категорий',
			'#options'=>$fcats,
			'#empty_option'=>'не выборано',
			'#default_value'=>empty($fd['termfield'])?'':$fd['termfield'],
			'#required'=>true,
		),
	);
	return $form;
}
//=========================================
function galls_config_form_cbjs($form,$form_state)
{
	$cmd=array();
	$te=$form_state['triggering_element'];
	if ($te['#name']=='gall-is')
		$cmd[]=ajax_command_replace('.gallparams-wrapper',render($form['gallparams']));
	return array('#type'=>'ajax','#commands'=>$cmd);
}
//================================================
function galls_config_form_submit($form,$form_state)
{
	$fd=variable_get('context-token-imgs-data',array());
	form_state_values_clean($form_state);
	$fd['gp']=$form_state['values'];
	variable_set('context-token-imgs-data',$fd);
	drupal_set_message('настройки сохранены');
}
?>