<?php
function ddcallbacksettings_form()
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
	$fd=variable_get('ding-dong-settings',array());
	$form['tomail']=array(
		'#type'=>'textfield',
		'#title'=>'Ящик, на который отсылать заявки',
		'#default_value'=>empty($fd['tomail'])?'':$fd['tomail'],
		'#required'=>true,
	);
	return $form;
}
// ===========================================
function ddcallbacksettings_form_submit($form,$form_state)
{
	form_state_values_clean($form_state);
	variable_set('ding-dong-settings',$form_state['values']);
	drupal_set_message('Настройки сохранены');
}
?>