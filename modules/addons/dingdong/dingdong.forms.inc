<?php
function dingdong_forms($form_id,$args)
{
	$forms=array();
	if (preg_match('#dingdongform_(\w+)#',$form_id,$type))
	{
		$type=preg_replace('#_.*$#is','',end($type));
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
	$classes=array(
		"dingdongform-{$form_state['fkey']}",
		'dingdongform-form',
		"site-$type-form",
		preg_match('#-fromajax-#i',$form_state['build_info']['form_id'])?'form-popup':'inline-form',
	);
	$fd=variable_get('ding-dong-settings',array());
	$fl=empty($fd['formslist'])?array():$fd['formslist'];
	$fd=array();
	foreach($fl as $f)
		if ($f['formid']==$type)
			$fd=$f;

	if (!$fd)
		return array('err'=>array(
			'#markup'=>'<b class="error">Форма не определена</b>',
		));
	//fromajax
	$fd['fields']=drupal_json_decode($fd['fields']);
	$form_state['formdata']=$fd;

	$form=$fd['fields'];
	$form['#attributes']=array(
		'class'=>$classes,
	);
	$form['actions']=array(
		'#type'=>'actions',
		'submit'=>array(
			'#type'=>'submit',
			'#value'=>empty($fd['buttitl'])?'Отправить':$fd['buttitl'],
			'#ajax'=>array(
				'callback'=>'dingdongform_form_jscb',
				'progress'=>array(
					'type'=>'fancyloader',
				),
			),
		),
	);
	
	//drupal_alter('dingdongform',$form,$type);
	//dsm($form,'ff');
	return $form;
}
// ==========================================
function dingdongform_form_jscb($form,$form_state)
{
	$cmd=array();
	// замена формы .. 
	$cl='dingdongform-'.$form_state['fkey'];
	$form['errmess']=array(
		'#theme'=>'status_messages',
		'#weight'=>-1,
	);
	// закрыть форму . оставить одно сообщение ...
	if (!form_get_errors() && preg_match('#closeaftersubmit$#i',$form_state['build_info']['form_id']))
		$form=array('errmess'=>$form['errmess']);
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
	$fd=$form_state['formdata'];
	$rows=array();
	foreach($vals as $k=>$v)
		$rows[]=array($form[$k]['#title'],$v?$v:'-');	
	$rows=theme('table',array(
		'caption'=>$form['#title'],
		'header'=>array('Поле','Значение'),
		'rows'=>$rows,
		'sticky'=>false,
	));
	//$fd=variable_get('ding-dong-settings',array());
	$headers=implode('',$headers);

	drupal_set_message(empty($fd['sumess'])?'Сообщение успешно отправлено.':$fd['sumess']);
	if (!empty($fd['tomails']))
		mail($fd['tomails'],empty($fd['mailtitle'])?'Письмишко!':$fd['mailtitle'],$rows,$headers);
}	
//=========================================================
// вернуть форму во в сплывающее окно .. 
function ding_dong_get_form()
{
	$post=$_POST;
	if (empty($post['formid']))
		return;
	$cmd=array();
	$form=drupal_get_form('dingdongform_'.$post['formid'].'_'.user_password().'-fromajax-closeaftersubmit');
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