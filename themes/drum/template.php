<?php
/*
http://masterskayalestnic.ru/
http://new.metaler.org/

*/
//======================================
function drum_js_alter(&$js)
{
	$js['misc/jquery.js']['data']=drupal_get_path('theme','drum').'/jquery.min.js';
}
// =========================================

//=======================================
function drum_theme()
{
	return array(
		'menu_div_wrapp'=>array(
			'render element'=>'c',
		),
		'customccs'=>array(
			'variables'=>array(
				'colormas'=>array(),// цвета 
				'widthmas'=>array(), // ширины
				'wklwiklmas'=>array(), 
			),
			'template'=>'customccs',
		),
	);
}
/// ============================
function drum_block_view_alter(&$data,$block)
{
	if (in_array($block->region,array('sidebar_first','sidebar_second')))
	{
		// лезем проверять пути .. 
		$acc=current_path()=='galls';
		if (!$acc && preg_match('#^node/(\d+)$#',current_path(),$nid))
		{

			// проверяем ноды .. 
			$res=db_select('node','n');
			$res->condition('n.nid',$nid);
			$res->condition('n.type','gall');
			$res->addExpression('count(*)');
			$acc=$res->execute()->fetchField()==1;
		}
		// если мы га главной галерее или на страницах галерей .. = скрываем боковые блоки ..
		if ($acc)
			$data['content']='';
		
	}
}
//=================================================
function drum_menu_div_wrapp($vars)
{
	return '<div class="submenu-wrapp">'.$vars['c']['#children'].'</div>';
}
// =================================================
function drum_preprocess_menu_link(&$vars)
{
	if ($vars['element']['#original_link']['menu_name']=='main-menu' && $vars['element']['#below'])
		$vars['element']['#below']['#theme_wrappers'][]='menu_div_wrapp';
		
}
//=======================================================
function drum_preprocess_page(&$vars)
{
	drupal_add_css('http://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css','external');
	// добавляем своих стидей ..  в кучу .. 
	
	$themmas=array();

	// цвета
	$colormas=theme_get_setting('colored');
	if ($colormas)
		$themmas['colormas']=$colormas;

	// флажки
	$wklwikl=theme_get_setting('wklwikl');
	if ($wklwikl)
		$themmas['wklwiklmas']=$wklwikl;

	// размеры 
	$widthmas=theme_get_setting('widthed');
	if ($widthmas)
		$themmas['widthmas']=$widthmas;

	$css=theme('customccs',$themmas);
	drupal_add_css($css,array(
		'type'=>'inline',
		'weight'=>-100,
		'group'=>CSS_THEME,
	));

	
	// доп стили 
	$cssaddons=theme_get_setting('css-addons');
	if($cssaddons)
		drupal_add_css($cssaddons,array(
			'type'=>'inline',
			'weight'=>-100,
			'group'=>CSS_THEME,
		));	
	
	$vars['page']['content']['main-sys']=array(
		'#weigth'=>-10,
		'title'=>array(
			'#prefix'=>'<h1>',
			'#markup'=>drupal_get_title(),
			'#suffix'=>'</h1>',
		),
		'mess'=>array(
			'#markup'=>theme('status_messages'),
		),
		'tabs'=>$vars['tabs'],
	);
	uasort($vars['page']['content'],'element_sort');
	// замена токенов
	drupal_alter('basemod_token_dd_replacer',$vars);
	dsm('sad');
	//kprint_r($vars);
}
// =======================================================
function drum_preprocess_region(&$vars)
{
	if ($vars['region']=='shead-menu')
		$vars['content']='<div class="reg-wrapp1"><div class="reg-wrapp2">'.$vars['content'].'</div></div>';
		
}
// ========================================================

// =============================================================
function drum_breadcrumb($vars)
{
	if ($vars['breadcrumb'])
	{
		$n=menu_get_object();
		if (isset($n->type))
			switch($n->type)
			{
				case 'news':
					$vars['breadcrumb'][]=l('Новости','news');
				break;	
				case 'gall':
					$vars['breadcrumb'][]=l('Галереи','galls');
				break;
			}

		$vars['breadcrumb'][]=menu_get_active_title();
		
	}
	$socnet=theme_get_setting('soc-net');
	if($socnet)
		$socnet='<div class="soc-net">'.$socnet.'</div>';

	if ($socnet || $vars['breadcrumb'])
		return '<div class="breadcrumb">'.$socnet.implode('<span class="sepor"></span>',$vars['breadcrumb']).'</div>';
	return '';
}
// ========================================================
function drum_form_alter(&$form,$form_state,$form_id){
	// styled-forms
	$wklwikl=theme_get_setting('wklwikl');
	if (!empty($wklwikl['styled-forms']))
		$form['#attributes']['class'][]='styled-forms';

	
}
?>