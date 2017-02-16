(function($){
	Drupal.behaviors.popupinit={
		attach:function(c,s){
			$('a.ding-dong-popupform').once(function(){
				$(this).on('click',function(e){
					e.preventDefault();
					var ajax= new Drupal.ajax(false,false,{
						url:'/ding-dong-get-form/'+this.rel
					});
					ajax.eventResponse(ajax);

				});
			});
		}
	};
})(jQuery);

