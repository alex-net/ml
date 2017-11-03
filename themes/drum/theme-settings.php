<?php
// настройик темы 
function drum_form_system_theme_settings_alter(&$form,&$form_state)
{
	$data=array(
		'colored'=>array(
			'#titl'=>'настройка цветов',
			'text_body'=>array('titl'=>'Текст содержимого'),
			'bg_document'=>array('titl'=>'Фон страницы'),
			'breadcrumb_text'=>array('titl'=>'Цвет ссылок хлебных крошек',),
			'link_text'=>array('titl'=>'Цвет ссылок в контенте',),
			'label_form_color'=>array('titl'=>'Цвет надписей форм в контенте',),
			'form_element_bgcolor'=>array('titl'=>'Фон форм в контенте',),
			'bg_head'=>array('titl'=>'Фон шапки'),
			'bg_headmenu_and_line'=>array('titl'=>'Фон менюшки в шапке и полоски'),
			'border_headmenu'=>array('titl'=>'Цвет бордюры меню в шапке'),
			'sidebarblocks_titlbg'=>array('titl'=>'Боковые блоки фон заголовка'),
			'sidebarblocks_titlcolor'=>array('titl'=>'Боковые блоки цвет заголовка'),
			'sidebarblocks_bodybg'=>array('titl'=>'Боковые блоки фон содержимого'),
			'sidebarblocks_bodycolor'=>array('titl'=>'Боковые блоки цвет содержимого'),
			'sidebarmenus_bodylinkcolor'=>array('titl'=>'Боковые меню цвет ссылок'),
			'headfootermenus_bodylinkcolor'=>array('titl'=>'Меню в шапке и подвале цвет ссылок'),
			'footer_bg'=>array('titl'=>'Подвал Фон'),
			'footer_text'=>array('titl'=>'Подвал цвет текста'),
		),
		'widthed'=>array(
			'#titl'=>'настройка размеров',
			'mincontentwidth'=>array('titl'=>'минимальная ширина контента'),
			'maxcontentwidth'=>array('titl'=>'Максимальная ширина контента'),
			'sidebarssize'=>array('titl'=>'Размер боковушек'),
			'sizefonthfmeni'=>array('titl'=>'Размер шрифта мешюшек (шапка/подвал)'),
		),
		'wklwikl'=>array(
			'verical_lines_in_footer_head_menu'=>'Вертикальные полоски в меню (шапка подвал)',
			'shadow_in_footer_head_menu'=>'Тени в меню (шапка подвал)',
			'showconsolemenu_footer_head_menu'=>'выпирания и уголки в меню (шапка подвал)',
			'showtopandbottombotder_footer_head_menu'=>'Показывать верхнюю и нижнюю бордюру у меню в шапке и подвале',
			'widthastablecell_footer_head_menu'=>'Вытянуть меню по ширине (шапка подвал)',
			'region_sadow'=>'тени у регионов',
			
		),
	);
	// достаём сохранённые данные ..
	foreach($data as $x=>$y)
	{
		if ($x=='wklwikl'){
			$form[$x]=array(
				'#type'=>'checkboxes',
				'#title'=>'Флажки',
				'#options'=>$y,
				'#default_value'=>theme_get_setting($x),

			);	
			continue;
		}
		$fd=theme_get_setting($x);
		//dsm($fd,'fd');
		foreach($fd as $k=>$v)
			if (isset($data[$x][$k]))
				$data[$x][$k]['val']=$v;
		
		$form[$x]=array(
			'#type'=>'fieldset',
			'#tree'=>true,
			'#title'=>$y['#titl'],
			'#attributes'=>array(
				'class'=>array('color-tail-wrapper'),
			),
		);
		$def='';
		$elclass=array();
		if ($x=='colored')
		{
			$form[$x]['#attached']=array(
				'library'=>array(
					array('system','farbtastic'),
				),
				'js'=>array(drupal_get_path('theme','drum').'/farb-color.js'),
				'css'=>array(drupal_get_path('theme','drum').'/farb-color.css'),
			);
			$def='#000000';
			$elclass[]='color-control';
		}
		
		foreach(element_children($data[$x]) as $k)
			$form[$x][$k]=array(
				'#type'=>'textfield',
				'#title'=>$data[$x][$k]['titl'],
				'#size'=>10,
				'#default_value'=>empty($data[$x][$k]['val'])?$def:$data[$x][$k]['val'],
				'#attributes'=>array(
					'class'=>$elclass,
				),
			);
	
	}
	$form['css-addons']=array(
		'#type'=>'textarea',
		'#title'=>'Дополнительные стили',
		'#default_value'=>theme_get_setting('css-addons'),
	);
	// код соцсетей .. 
	$form['soc-net']=array(
		'#type'=>'textarea',
		'#title'=>'Код соц сетей',
		'#default_value'=>theme_get_setting('soc-net'),
	);
	

}
?>