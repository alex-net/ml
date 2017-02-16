jQuery(function($){
	var points=Drupal.settings["footer-map"].points;
	var map;
	if(points.length &&0)
	{
		$('.footer-wrapper').prepend('<div class="footer-map-place"></div>');
		$('.footer-map-place').css('height',Drupal.settings["footer-map"].mh+'px');
		ymaps.ready(function(){
			map=new ymaps.Map($('.footer-map-place')[0],{
				center:[55,33],
				zoom:10,
				controls:[]
			},{});
			var gc=new ymaps.Clusterer({
				clusterIconColor:'#241616'
			});
			for(k in points)
			{
				gc.add(new ymaps.Placemark(points[k].point,{
					hintContent:points[k]['name'],
					ballonContentBody:points[k]['addres']
				},{
					iconColor:'#241616'
				}));
				//console.log(points[k]);
			}
			map.geoObjects.add(gc);
			map.setBounds(gc.getBounds());
		});	
		// добавляем точки .
		
	}

});