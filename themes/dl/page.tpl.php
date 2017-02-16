<div class="all-page-wrapper">
	<div class="site-head-wrapper ">
		<div class="site-head">
			<div class="logo-telephone">
				<!-- <a href="<?php echo $front_page;?>"><img src="<?php echo $logo;?>" alt='logo'/></a> -->
			</div>
			<?php echo render($page['head-site-manu']);?>
		</div>
		<div class="h-zub"></div>
	</div>
	<?php echo render($page['before-content']);?>
	<div class="s-content-wrapper">
		
		<div class="beadcrumbs">
			<?php echo $breadcrumb;?>
			
		</div>
		<?php echo $messages;?>
		<?php if($title):?>
			<h1 class="pattern"><?php if(!empty($node) && $node->type == "geo_page"){echo "Деревянные лестницы в ";}echo $title;?></h1>
		<?php endif;?>
		<?php echo render($tabs);?>
		<?php echo render($page['content']);?>
	</div>	
</div>
<?php echo render($page['footer']);?>
