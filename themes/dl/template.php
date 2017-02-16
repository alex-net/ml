<?php
function dl_js_alter(&$js)
{
	$themepath=drupal_get_path('theme','dl');
	$js['misc/jquery.js']['data']=$themepath.'/jquery.min.js';
	if (!isset($js['misc/jquery.form.js']))
		$js['misc/jquery.form.js']=array();
	$js['misc/jquery.form.js']=array_merge($js['misc/jquery.form.js'],array(
		'data'=>$themepath.'/jquery.form.min.js',
		'scope'=>'header',
		'group'=>JS_THEME,
		'every_page'=>true,
		'type'=>'file',
		'weight'=>10,
		'defer'=>false,
		'cache'=>true,
		'preprocess'=>true,
	));

	//dsm($js);
}

// =========================================================
function dl_preprocess_region(&$vars)
{
	switch($vars['region'])
	{
		case 'footer':
			$vars['content']='<div class="f-zub"></div><div class="footer-wrapper"><div class="wrapp2">'.$vars['content'].'</div></div>';
		break;
	}
}
//========================================================
function dl_breadcrumb($vars)
{
	$b=$vars['breadcrumb'];
	$blus=array();
	$term=array('tid'=>0,'name'=>'');
	if (drupal_is_front_page())
		return '';
	$cp=current_path();
	if ($cp=='galls')
		$b[]='<span class="last-ell">Наши работы</span>';
	if (preg_match('#node/(\d+)#',$cp,$nid))
	{
		$nid=end($nid);
		$res=db_select('node','n');
		$res->condition('n.nid',$nid);
		$res->fields('n',array('nid','title'));
		// пристыковываем термин. .. 
		$res->leftJoin('field_data_field_catgall','cat','cat.entity_id=n.nid and cat.bundle=n.type');
		$res->leftJoin('taxonomy_term_data','td','td.tid=cat.field_catgall_tid');
		$res->fields('td',array('tid','name'));
		$res=$res->execute()->fetch(PDO::FETCH_ASSOC);
		//dsm($res);
		if ($res['tid'])
			$b[]=l($res['name'],'taxonomy/term/'.$res['tid']);
		$b[]='<span class="last-ell">'.$res['title'].'</span>';
		//$term=$res;
	}
	
	if (preg_match('#taxonomy/term/(\d+)#',$cp,$tid))
	{

		$res=db_select('taxonomy_term_data','t');
		$res->condition('t.tid',end($tid));
		$res->fields('t',array('name'));
		$res=$res->execute()->fetchField();
		$b[]='<span class="last-ell">'.$res.'</span>';
	}
	return '<div class="bread-wrapp"><span class="br-ico"></span>'.implode('',$b).'</div>';
}
// =======================================================
function dl_page_alter($p)
{

	$data=array(
		'points'=>variable_get('yamapdata',array()),
	);
	drupal_add_js(array('footer-map'=>$data),'setting');
}

?>