<?php 
function mjobs_block_info()
{
	return array(
		'map-jobs'=>array(
			'info'=>'Карта населённых пунктов',
		),
	);
}
// ===========================================
function mjobs_block_configure($delta='')
{
	$form=array();
	$set=variable_get('block-data-'.$delta,array());
	switch($delta)
	{
		case 'map-jobs':
			$cityes=empty($set['mapscitypoints'])?'':$set['mapscitypoints'];
			$cityeshash=md5($cityes);
			$form['block-data']=array(
				'#type'=>'fieldset',
				'#tree'=>true,
				'#title'=>'Настройка карты',
				'map-height'=>array(
					'#type'=>'textfield',
					'#title'=>'Высота карты',
					'#default_value'=>empty($set['map-height'])?0:$set['map-height'],
					'#description'=>'Например 500px или 10em',
				),
				'htmlinblock'=>array(
					'#type'=>'textarea',
					'#title'=>'Текст на карте',
					'#default_value'=>empty($set['htmlinblock'])?'':$set['htmlinblock'],
				),
				'mapscitypoints'=>array(
					'#type'=>'textarea',
					'#required'=>true,
					'#title'=>'Координаты точек на карте',
					'#default_value'=>$cityes,
					'#rows'=>6,
				),
				'mapscitypointshash'=>array(
					'#type'=>'value',
					'#value'=>$cityeshash,
				),
				'points'=>array(
					'#type'=>'value',
					'#value'=>empty($set['points'])?array():$set['points'],
				),
			);
		break;
	}
	return $form;
}
// ==============================================
function mjobs_block_save($delta='',$edit=array())
{
	variable_set('block-data-'.$delta,$edit['block-data']);
	if ($delta=='map-jobs' && md5($edit['block-data']['mapscitypoints'])!=$edit['block-data']['mapscitypointshash'])
	{
		$prefix='Россия, Московская область, ';
		$r=array_map('trim',explode("\n",trim($edit['block-data']['mapscitypoints'])));

		$opt=array('kind'=>'locality','format'=>'json'); 
		$url='https://geocode-maps.yandex.ru/1.x';
		$dat=array();
		foreach($r as $a)
		{
			if (!preg_match('#Россия#is',$a))
				$a=$prefix.$a;
			
			$opt['geocode']=$a;
			$data=drupal_http_request($url.'?'.drupal_http_build_query($opt));
			if ($data->code==200)
			{
				$data=drupal_json_decode($data->data);
				$data=reset($data);
				$data=reset($data);			
			
			
				if (!empty($data['metaDataProperty']['GeocoderResponseMetaData']['found']))
				{
					$o=reset($data['featureMember']);
					$o=$o['GeoObject'];
					$dat[]=array(
						'point'=>array_reverse(explode(' ',$o['Point']['pos'])),
						'name'=>$o['name'],
						'address'=>$o['metaDataProperty']['GeocoderMetaData']['text'],
					);
				}
			}
		}
		$edit['block-data']['points']=$dat;
		variable_set('block-data-'.$delta,$edit['block-data']);
		drupal_set_message('Поле адресов обновлено');
		//variable_set('yamapdata',$dat);

	}
}
//===============================================
function mjobs_block_view($delta='')
{
	$b=array();
	$set=variable_get('block-data-'.$delta,array());
	switch($delta)
	{
		case 'map-jobs':
			// mjobs
			$b['content']=array(
				'map'=>array(
					'#type'=>'container',
					'#attributes'=>array(
						'class'=>array('footer-map-place'),
						'style'=>'',

					),
					'#attached'=>array(
						'library'=>array(
							array('basemod','ymaps'),
						),
						'js'=>array(
							array(
								'data'=>drupal_get_path('module','mjobs').'/map-obj-city.js',
								'type'=>'file',
							),
							array(
								'data'=>array('map-jobs-points'=>$set['points']),
								'type'=>'setting',
							),
						),
					),
				),
			);
			// points
			if (!empty($set['map-height']))
				$b['content']['map']['#attributes']['style']='height:'.$set['map-height'];
			if (!empty($set['htmlinblock']))
				$b['content']['map']['inblocktext']=array(
					'#markup'=>$set['htmlinblock'],
					'#prefix'=>'<div class="inblocktext-wrap">',
					'#suffix'=>'</div>',
				);
		break;
	}
	return $b;
}
?>