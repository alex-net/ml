<div class="gall-main-page">
<?php foreach($out as $v):?>
	<h3><?php echo $v['name'];?></h3>
	<?php echo render($v['nids']);?>
<?php endforeach;?>
</div>