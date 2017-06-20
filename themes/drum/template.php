<?php
/*
http://masterskayalestnic.ru/
http://new.metaler.org/

*/
//======================================
function drum_js_alter(&$js)
{
	$js['misc/jquery.js']['data']='http://ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js';
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
			'render element'=>'colormas',
			'template'=>'customccs',
		),
		'customwidth'=>array(
			'render element'=>'widthmas',
			'template'=>'customwidth',
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
	// цвета
	$colormas=theme_get_setting('colored');
	if ($colormas)
	{
		$css=theme('customccs',array('colormas'=>$colormas));
		drupal_add_css($css,array(
			'type'=>'inline',
			'weight'=>-100,
			'group'=>CSS_THEME,
		));
	}
	// размеры 
	$widthmas=theme_get_setting('widthed');
	if ($widthmas)
	{
		$css=theme('customwidth',array('widthmas'=>$widthmas));
		drupal_add_css($css,array(
			'type'=>'inline',
			'weight'=>-100,
			'group'=>CSS_THEME,
		));
	}
	// доп стили 
	$cssaddons=theme_get_setting('css-addons');
	if($cssaddons)
		drupal_add_css($cssaddons,array(
			'type'=>'inline',
			'weight'=>-100,
			'group'=>CSS_THEME,
		));	


	$vars['page']['content']['main-sys']=array(
		'#weight'=>0,
		'title'=>array(
			'#prefix'=>'<h1>',
			'#markup'=>drupal_get_title(),
			'#suffix'=>'</h1>',
		),
		'mess'=>array(
			'messuc'=>array(
				'#markup'=>theme_status_messages(array('display'=>'error')),
			),
			'messuc'=>array(
				'#markup'=>theme_status_messages(array('display'=>'warning')),
			),
			'messuc'=>array(
				'#markup'=>theme_status_messages(array('display'=>'status')),
			),
		),
		'tabs'=>$vars['tabs'],
	);
	uasort($vars['page']['content'],'drupal_sort_weight');


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
	return '<div class="breadcrumb">'.$socnet.implode('<span class="sepor"></span>',$vars['breadcrumb']).'</div>';
}
?>