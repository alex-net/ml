(function($){
	Drupal.behaviors.ajaxfancyinit={
		attach:function(c,s){
			$('body').once(function(){
				if (typeof Drupal.ajax =='undefined')
					return;
				// --------------------------
				var bs=Drupal.ajax.prototype.beforeSend;
				Drupal.ajax.prototype.beforeSend=function(){
					bs.apply(this,arguments);
					if (this.progress.type=='fancyloader')
						jQuery.fancybox.showLoading();
				}
				var su=Drupal.ajax.prototype.success;
				Drupal.ajax.prototype.success=function(){
					su.apply(this,arguments);
					if (this.progress.type=='fancyloader')
						jQuery.fancybox.hideLoading();		
				}
				var er=Drupal.ajax.prototype.error;
				Drupal.ajax.prototype.error=function(){
					er.apply(this,arguments);
					if (this.progress.type=='fancyloader')
						jQuery.fancybox.hideLoading();		
				}
				//------------------ комманды -----------------------
				// окошко с fancybox .... 
				Drupal.ajax.prototype.commands.showmessage=function(e,r,s){

					$.fancybox.open({
						title:r.title,
						fixed:false,
						content:r.content,
						wrapCSS:'fancy-popup-content',
						ajaxdata:r.ajax,
						afterShow:function(){
							Drupal.attachBehaviors(this.inner);
						}
					});
				}
				//----------------------------------------------------
				/// обновить окошко fb
				Drupal.ajax.prototype.commands.fancyboxwindupd=function(){
					if($.fancybox.isOpened)
						$.fancybox.update();
				}
				// ----------------------------------------------------
				// закрыть окошко fancybox
				Drupal.ajax.prototype.commands.fancyboxwindclose=function(){
					$.fancybox.close();
				}

				// ----------------------
			});
		}
	};
	// настройки галереи ..  
	Drupal.behaviors.gallpopupinit={
		initgall:function(e){
			e.preventDefault();
			var fancygal=$('a[rel="'+this.rel+'"]');
			$.fancybox.open(fancygal,{index:fancygal.index(this)});
		},
		attach:function(c,s){
			// внутри галереи .. 
			$('.node-gall-full').once(function(){
				$(this).find('.field-type-image a').attr('rel','gall').on('click',Drupal.behaviors.gallpopupinit.initgall);
			
			});
			/// отдельные блоки вставленные через токены
			$('.gall-block-wrapper, .content-token-imgs-wrapp').once(function(ind){
				$(this).find('a').attr('rel','gall-'+ind).on('click',Drupal.behaviors.gallpopupinit.initgall);
			});
		}
	};
	// ================================
	/// вставка в поле textarea некого символа 
	function _putchartotextarea(objta,char){
		var obj = $(objta)[0];
		var start = obj.selectionStart;
		var end = obj.selectionEnd;
		var before = obj.value.substring(0, start);
		var after = obj.value.substring(end, obj.value.length);

		obj.value = before + char + after;
		// устанавливаем курсор
		obj.setSelectionRange(start+1, start+1);
	}
	//=======================================================
	// разрешаем таб в textarea
	Drupal.behaviors.textareatabkeyallow={
		attach:function(c,s){
			$('textarea.allow-tab-key').once(function(){
				$(this).keypress(function(e){
					if(e.keyCode==9){
						e.preventDefault();
						_putchartotextarea($(this),"\t");
					}
				});
			});
		}
	}
})(jQuery)