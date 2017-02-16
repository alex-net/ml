<?php 
function galls_view_cb()
{
	$fd=variable_get('context-token-imgs-data',array());
	if (empty($fd['gp']))
		return array();
	$fd=$fd['gp'];
	
	$res=db_select('node','n');
	$res->condition('n.type',$fd['gall-is']);
	$res->condition('n.status',1);
	$res->fields('n',array('nid'));
	$res->leftJoin('field_data_'.$fd['termfield'],'t','t.entity_id=n.nid and t.bundle=n.type');
	$res->leftJoin('taxonomy_term_data','td','td.tid=t.'.$fd['termfield'].'_tid');
	
	$res->fields('td',array('tid','name','weight'));
	$res=$res->execute()->fetchAll(PDO::FETCH_ASSOC);
	$out=array();
	foreach($res as $v)
	{
		if (!isset($out[$v['tid']]))
			$out[$v['tid']]=array(
				'name'=>$v['name'],
				'nids'=>array(),
				'weight'=>$v['weight'],
			);
		$out[$v['tid']]['nids'][]=$v['nid'];
	}
	foreach($out as $k=>$v)
		$out[$k]['nids']=node_view_multiple(node_load_multiple($v['nids']));
	uasort($out,'drupal_sort_weight');
	return theme('gall_page_view',array('out'=>$out));
}
?>