<div class="all-page-wrapper">
	<div class="s-head">
		<div class="bottom-footer-line"><div class="light-line"></div></div>
		<?php //echo render($page['shead']);?>
		<?php echo render($page['shead']);?>
		
		<?php echo render($page['shead-menu']);?>
		
	</div>
	<div class="page-all-content clearfix">
		<?php echo render($page['content-before']);?>
		<?php echo $breadcrumb;?>
		<?php echo render($page['sidebar_first']);?>
		<?php echo render($page['sidebar_second']);?>
		
		<?php echo render($page['content']);?>
	</div>
	<?php echo render($page['subfooter']);?>
	<?php echo render($page['sfooter']);?>
</div>