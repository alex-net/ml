jQuery(function($){
	// цепляем шапку .. под потолок .. 
	$(window).scroll(function(){
		//var wh=$(window).height();
		var wst=$(window).scrollTop();
		var mo=$('.region-shead-menu').offset();
		var bo=$('body').offset();
		var rsh=$('.region-shead').height();
		
		if (rsh>=wst && $('.s-head').hasClass('fixed'))
		{
			$('.s-head').removeClass('fixed');
			$('.s-head').next().removeAttr('style');
		}
		if(mo.top-bo.top<wst && !$('.s-head').hasClass('fixed'))
		{
			h2=$('.s-head').height();//-rsh;
			$('.s-head').next().css('padding-top',h2+'px');
			$('.s-head').addClass('fixed');
		}

	}).scroll();
	// манипулируем вторыми уровнями меюшки .. 
	/*$('.stroitel-menu .content  ul li a').click(function(e){
		if ($(this).parent().find('ul').size())
		{
			e.preventDefault();
			$(this).parent().find('ul').eq(0).slideToggle(500);
		}
		e.stopPropagation();
	});*/
	// слайдер .. 
	/*
	$('.site-slider .field-name-field-slider-img .field-items').slick({
		infinite:true,
		autoplay:true,
		arrows:false
	});*/
	

});