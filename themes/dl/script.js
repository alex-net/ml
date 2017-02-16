(function($){
	Drupal.behaviors.sitetodo={
		attach:function(c,s){
			$('body').once(function(){
				$(window).on('scroll',function(){
					if ($(this).scrollTop()>$('.logo-telephone').height())
					{
							$('.all-page-wrapper .region-before-content').css({
								'padding-top':$('.all-page-wrapper .site-head-wrapper .logo-telephone').height()
							});
							$('.all-page-wrapper').addClass('fixed');

					}
					else
					{
						$('.all-page-wrapper').removeClass('fixed');
						$('.all-page-wrapper .region-before-content').css({
								'padding-top':0
							});
					}
				});
				
				
			});
		}
	};
})(jQuery);

