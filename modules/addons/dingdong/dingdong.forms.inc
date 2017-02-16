<?php
function dingdong_forms($form_id,$args)
{
	$forms=array();
	if (preg_match('#dingdongform_(\w+)#',$form_id,$type))
	{
		$type=preg_replace('#_\d+#is','',end($type));
		array_unshift($args,$type);
		$forms[$form_id]=array(
			'callback'=>'dingdongform_form',
			'callback arguments'=>$args,
		);
	}
	return $forms;
}
// ==================================================
function dingdongform_form($form,&$form_state,$type='')
{
	unset($form_state['input']);
	if (empty($form_state['fkey']))
		$form_state['fkey']=$type.'-'.user_password(15);
	$form=array(
		'#attributes'=>array(
			'class'=>array("dingdongform_{$form_state['fkey']}"),
		),
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
				'#ajax'=>array(
					'callback'=>'dingdongform_form_jscb',
					'progress'=>array(
						'type'=>'fancyloader',
					),
				),
			),
		),
	);
	drupal_alter('dingdongform',$form,$type);
	//dsm($form,'ff');
	return $form;
}
// ==========================================
function dingdongform_form_jscb($form,$form_state)
{
	$cmd=array();
	// замена формы .. 
	$cl='dingdongform_'.$form_state['fkey'];
	$form['errmess']=array(
		'#theme'=>'status_messages',
		'#weight'=>-1,
	);

	$cmd[]=ajax_command_replace('form.'.$cl,render($form));
	$cmd[]=array(
		'command'=>'fancyboxwindupd',
	);

	return array('#type'=>'ajax','#commands'=>$cmd);
}
//================================================================
function dingdongform_form_submit($form,$form_state)
{
	$headers=array(
		"MIME-Version: 1.0\r\n",
		"content-type:text/html;charset=utf8\r\n",
	);
	form_state_values_clean($form_state);
	$vals=$form_state['values'];
	$rows=array();
	foreach($vals as $k=>$v)
		$rows[]=array($form[$k]['#title'],$v?$v:'-');	
	$rows=theme('table',array(
		'caption'=>$form['#title'],
		'header'=>array('Поле','Значение'),
		'rows'=>$rows,
		'sticky'=>false,
	));
	$fd=variable_get('ding-dong-settings',array());
	$headers=implode('',$headers);
	drupal_set_message('Сообщение успешно отправлено.');
	$r=mail($fd['tomail'],$form['#title'],$rows,$headers);

}
//=========================================================
// вернуть форму во в сплывающее окно .. 
function ding_dong_get_form($type)
{
	$cmd=array();
	$form=drupal_get_form('dingdongform_'.$type,user_password());
	$formr=render($form);
	$js=drupal_add_js();
	$ajax=array();
	foreach($js['settings']['data'] as $v)
		if (isset($v['ajax']))
			$ajax=array_merge($ajax,$v['ajax']);
	$cmd[]=array(
		'command'=>'showmessage',
		'content'=>$formr,
		'title'=>empty($form['#title'])?'':$form['#title'],
		'ajax'=>$ajax,
	);
	return array('#type'=>'ajax','#commands'=>$cmd);
}
?>