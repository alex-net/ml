<?php 
function dl_form_system_theme_settings_alter(&$form,$form_state)
{
	//dsm($form);

	$form['#submit'][]='dlsettingsthemesubmit';
}

// ==============================================
function dlsettingsthemesubmit($form,$form_state)
{

}
?>