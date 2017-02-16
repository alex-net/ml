jQuery(function($){
	$('.color-tail-wrapper input.color-control').each(function(){
		var par=$(this).parent();
		par.append('<div class="farb-control"></div>').addClass('color-wrapper-el');
		par.find('div.farb-control').farbtastic(par.find('input'));
		par.find('input').focus(function(){
			par.find('div.farb-control').addClass('vis');
		}).blur(function(){
			par.find('div.farb-control').removeClass('vis');
		});

	});
		console.log('das');
});