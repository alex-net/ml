<?php
function ddcallbacksettings_form($form,&$form_state)
{
	$form=array(
		'actions'=>array(
			'#type'=>'actions',
			'submit'=>array(
				'#type'=>'submit',
				'#value'=>'Сохранить',
				'#name'=>'save',
			),
		),
	);
	unset($form_state['input']);
	$fd=variable_get('ding-dong-settings',array());
	
	$fl=empty($fd['formslist'])?array():$fd['formslist'];
	if (!empty($form_state['triggering_element']) && $form_state['triggering_element']['#name']=='addmore'){
		$fl=$form_state['values']['formslist'];
		foreach($fl as $x=>$y)
			if (empty($y['formid']))
				unset($fl[$x]);
		$fl[]=array();	
	}
	if (!$fl)
		$fl[]=array();
	$form['formslist']=array(
		'#type'=>'fieldset',
		'#title'=>'Список формы',
		'#tree'=>true,
		'#attributes'=>array(
			'class'=>array('forms-list'),
		),
		'formmore'=>array(
			'#type'=>'button',
			'#value'=>'добавить ещё',
			'#name'=>'addmore',
			'#weight'=>100,
			'#ajax'=>array(
				'callback'=>'ddcallbacksettings_form_jscb',
			),
		),
	);
	

	foreach($fl as $y){
		$form['formslist'][]=array(
			'formid'=>array(
				'#type'=>'textfield',
				'#title'=>'Form ID',
				'#description'=>'Должен быть уникальным',
				'#default_value'=>empty($y['formid'])?'':$y['formid'],
			),
			'buttitl'=>array(
				'#type'=>'textfield',
				'#title'=>'Надпись на кнопке',
				'#default_value'=>empty($y['buttitl'])?'':$y['buttitl'],
			),
			'sumess'=>array(
				'#type'=>'textfield',
				'#title'=>'Сообщение об успешной отправке',
				'#default_value'=>empty($y['sumess'])?'':$y['sumess'],
			),
			'titlform'=>array(
				'#type'=>'textfield',
				'#title'=>'Подпись формы',
				'#default_value'=>empty($y['titlform'])?'':$y['titlform'],
				'#description'=>'Появляется в попапе',
			),
			'tomails'=>array(
				'#type'=>'textfield',
				'#title'=>'Отправить данные формы на мыло(а)',
				'#default_value'=>empty($y['tomails'])?'':$y['tomails'],
			),
			'mailtitle'=>array(
				'#type'=>'textfield',
				'#title'=>'Загловок письма',
				'#default_value'=>empty($y['mailtitle'])?'':$y['mailtitle'],
			),
			'fields'=>array(
				'#type'=>'textarea',
				'#title'=>'Поля формы',
				'#description'=>'Объект в фиормате json',
				'#default_value'=>empty($y['fields'])?'':$y['fields'],
				'#attributes'=>array(
					'class'=>array(
						'allow-tab-key',
					),
				),
			),
			'hr'=>array('#markup'=>'<hr/>'),
		);
	}
	return $form;
}
//============================================
function ddcallbacksettings_form_validate(&$form,&$form_state){
	if ($form_state['triggering_element']['#name']=='save'){
		foreach(element_children($form['formslist']) as $k){
			$el=$form['formslist'][$k];
			if (!empty($el['formid']['#value'])) {

				if (empty($el['fields']['#value']))
					form_error($form['formslist'][$k]['fields'],'Нужно указать поля для формы '.$el['formid']['#value']);
				else
					if(!drupal_json_decode($el['fields']['#value']))
						form_error($form['formslist'][$k]['fields'],'Ошибка в заполнении полей для формы '.$el['formid']['#value']);
			}
		}
	}
}
// =========================================================
function ddcallbacksettings_form_jscb($form,$form_state){
	$cmd=array();
	$cmd[]=ajax_command_replace('.forms-list',render($form['formslist']));
	return array('#type'=>'ajax','#commands'=>$cmd);
}
// ===========================================
function ddcallbacksettings_form_submit($form,$form_state)
{
	form_state_values_clean($form_state);
	variable_set('ding-dong-settings',$form_state['values']);
	drupal_set_message('Настройки сохранены');
}
?>