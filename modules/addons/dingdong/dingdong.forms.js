(function($){
	Drupal.behaviors.dd={
		attach:function(c,s){
			$('.but-controll').once(function(){
				$(this).on('click',function(){
					var form=$(this).data('form');
					if (form){
						var ajax=new Drupal.ajax(false,false,{
							url:Drupal.settings.pathtogetdingdongsforms,
							submit:{
								formid:form
							}
						});
						ajax.eventResponse(ajax);
					}

				});
			});
			
		}
	}
})(jQuery);