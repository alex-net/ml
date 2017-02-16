<?php 
function dingdong_token_info()
{
	$toks=array(
		'dingdong'=>array(
			'callback'=>array(
				'name'=>'Форма обратной связи',
				'description'=>'Форма обратной связи',
			),
			'zakazat'=>array(
				'name'=>'Форма Заказа',
				'description'=>'Форма заказа',
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
		foreach($tokens as $name=>$orig)
			if (preg_match('#(callback|zakazat)#is',$name))
			{
				$name=preg_replace('#\W#s','_',$name);
				$form=drupal_get_form('dingdongform_'.$name);
				$form['#prefix']='<div class="site-inline-form">';
				$form['#suffix']='</div>';
				$rep[$orig]=render($form);
				
		
			}
		
	
	return $rep;
}
?>