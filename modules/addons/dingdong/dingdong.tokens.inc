<?php 
function dingdong_token_info()
{
	$toks=array(
		'dingdong'=>array(
			'get-dd-form'=>array(
				'name'=>'Показать форму',
				'description'=>'Загрузить форму',
			),
			'callback'=>array(
				'name'=>'Форма обратной связи',
				'description'=>'Форма обратной связи',
			),
			'zakazat'=>array(
				'name'=>'Форма Заказа',
				'description'=>'Форма заказа',
			),
			'but'=>array(
				'name'=>'Кнопка вызова всплывающей формы',
				'description'=>'Всплывашка',
			),
		),
	);
	$types=array(
		'dingdong'=>array(
			'name'=>'Формы обратной связи',
			'description'=>'Набор форм обратной связи',
		),
	);
	return array(
		'types'=>$types,
		'tokens'=>$toks,
	);
}
//======================================================
function dingdong_tokens($type,$tokens,$data=array(),$options=array())
{
	$rep=array();
	if ($type=='dingdong')
		foreach($tokens as $name=>$orig){
			$name=explode(':',$name);
			switch($name[0]){
				case 'get-dd-form':
					if (count($name)!=2)
						break;
					$form=drupal_get_form('dingdongform_'.$name[1].'_'.user_password());
					$rep[$orig]=render($form);
				break;
				// отображение формы
				case 'callback':
				case 'zakazat':
					$form=drupal_get_form('dingdongform_'.implode('_',$name));
					$form['#prefix']='<div class="site-inline-form">';
					$form['#suffix']='</div>';
					$rep[$orig]=render($form);	
				break;
				case 'but':
					if (count($name)!=3)
						break;
					$attr=array(
						'class'=>array('but-controll','but-for-'.$name[1],'show-in-popup'),
						'data-form'=>$name[1],
					);
					drupal_add_js(drupal_get_path('module','dingdong').'/dingdong.forms.js');
					drupal_add_js(array(
						'pathtogetdingdongsforms'=>'/ding-dong-get-form',

					),'setting');
					$rep[$orig]='<span '.drupal_attributes($attr).'>'.$name[2].'</span>';
				break;
			}
			
			
			/*if (preg_match('#^but\:#i',$name)){
				$name=explode(':',$name);
				dsm($name);
				
			}*/
		}
		
	
	return $rep;
}
?>