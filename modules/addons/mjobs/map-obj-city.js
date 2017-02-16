(function($){
	Drupal.behaviors.mapobjcity={
		attach:function(c,s){
			$('body').once(function(){

				var points=Drupal.settings["map-jobs-points"];
				var map;
				if(!points.length)
					return ;
				
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
					}
					map.geoObjects.add(gc);
					map.setBounds(gc.getBounds());
				});	
			});
			
		}
	};
})(jQuery);