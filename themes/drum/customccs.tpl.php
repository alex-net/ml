body {color:<?php echo $colormas['text_body'];?>;background:<?php echo $colormas['bg_document'];?>;}
.s-head {background:<?php echo $colormas['bg_head'];?>;}

.site-zakazat-form .form-item,.site-zakazat-form .form-submit  {background:<?php echo $colormas['bg_headmenu_and_line'];?>;border-radius:0.5em;}

.region-shead-menu .reg-wrapp1, .subfooter-menu .content{border-top:1px solid <?php echo $colormas['border_headmenu']?>;border-bottom:1px solid <?php echo $colormas['border_headmenu']?>;background:<?php echo $colormas['bg_headmenu_and_line'];?>;}
.s-head .bottom-footer-line {background:<?php echo $colormas['bg_headmenu_and_line'];?>;}

.region-sidebar-first .block h2, .region-sidebar-second .block h2 {background:<?php echo $colormas['sidebarblocks_titlbg'];?>;border-bottom:1px solid <?php echo $colormas['border_headmenu'];?>;}
.region-sidebar-first .block .content, .region-sidebar-second .block .content {background:<?php echo $colormas['sidebarblocks_bodybg'];?>;}

.region-sidebar-first .block .content ul.menu li a, .region-sidebar-second .block .content ul.menu li a {color:<?php echo $colormas['sidebarmenus_bodylinkcolor'];?>;}

.region-sfooter {background-color:<?php echo $colormas['footer_bg'];?>;}
.region-sfooter .block .content {color:<?php echo $colormas['footer_text'];?>;}
.s-head .bottom-footer-line {border-top:1px solid <?php echo $colormas['border_headmenu'];?>;border-bottom:1px solid <?php echo $colormas['border_headmenu'];?>;}
.region-sidebar-first .block, .region-sidebar-second .block {border:1px solid <?php echo $colormas['border_headmenu'];?>;}
.breadcrumb a,.breadcrumb {color:<?php echo $colormas['breadcrumb_text'];?>;}
#block-system-main .content a {color:<?php echo $colormas['link_text']?>;}

.s-main-menu .content > ul  li a, .subfooter-menu .content > ul  li a {color:<?php echo $colormas['headfootermenus_bodylinkcolor']; ?>}

.region-sidebar-first .block h2,.region-sidebar-second .block h2  {color:<?php echo $colormas['sidebarblocks_titlcolor'];?>}
.region-sidebar-first .block .content,.region-sidebar-second .block .content  {color:<?php echo $colormas['sidebarblocks_bodycolor'];?>}


.region-shead,.s-head,.region-shead-menu,.page-all-content,.region-subfooter,.region-sfooter {/*width:97.5em;*/max-width:<?php echo $widthmas['maxcontentwidth'];?>;min-width:<?php echo $widthmas['mincontentwidth'];?>;margin:0 auto;}

.sidebar-second .region-content {margin: 0 <?php echo $widthmas['sidebarssize'];?> 0 0.8em;overflow:hidden;}
.sidebar-first .region-content {margin: 0 0.8em 0 <?php echo $widthmas['sidebarssize'];?>;overflow:hidden;}
.two-sidebars .region-content {margin:0 <?php echo $widthmas['sidebarssize'];?>;overflow:hidden;}
.region-sidebar-first, .region-sidebar-second {width:calc(<?php echo $widthmas['sidebarssize'];?> - 1em);}
.s-main-menu .content > ul > li > a, .subfooter-menu .content > ul > li > a {font-size:<?php echo $widthmas['sizefonthfmeni'];?>;}


.site-inline-form .form-item label {color:<?php echo $colormas['label_form_color'];?>;}


<?php if (!empty($wklwiklmas['verical_lines_in_footer_head_menu'])):?>
.s-main-menu .content > ul > li > a,.subfooter-menu .content > ul > li > a{ border-left:1px solid rgba(0,0,0,0.3);}
<?php endif;?>
<?php if (!empty($wklwiklmas['shadow_in_footer_head_menu'])):?>
.region-shead-menu .reg-wrapp1,.subfooter-menu .content {box-shadow:0 0 1.2em -0.6em black;}
<?php endif;?>

<?php if (!empty($wklwiklmas['showconsolemenu_footer_head_menu'])):?>
.region-shead-menu .reg-wrapp1,.subfooter-menu .content {margin-left:-0.8em;margin-right:-0.8em;}
.region-shead-menu .reg-wrapp2:before, .subfooter-menu .content > ul:before {content:'';display:block;width:0.8em;height:0.8em;position:absolute;left:0;bottom:-0.9em;box-sizing:border-box;border-right:0.8em solid rgba(0,0,0,0.5);border-bottom:0.8em solid transparent;}
.region-shead-menu .reg-wrapp2:after, .subfooter-menu .content > ul:after {content:'';display:block;width:0.8em;height:0.8em;position:absolute;right:0;bottom:-0.9em;box-sizing:border-box;border-left:0.8em solid rgba(0,0,0,0.5);border-bottom:0.8em solid transparent;}
.region-sidebar-first .block .content:after {content:'';display:block;width:0.8em;height:0.8em;border-right:0.8em solid rgba(0,0,0,0.5);position:absolute;left:-0.05em;bottom:-0.8em;border-bottom:0.8em solid transparent;box-sizing:border-box;}
.region-sidebar-second .block .content:after {content:'';display:block;width:0.8em;height:0.8em;border-left:0.8em solid rgba(0,0,0,0.5);position:absolute;right:-0.05em;bottom:-0.8em;border-bottom:0.8em solid transparent;box-sizing:border-box;}
.s-head.fixed .region-shead-menu .reg-wrapp2:after, .s-head.fixed .region-shead-menu .reg-wrapp2:before {display:none;}
.region-sidebar-first {left:-0.8em;}
.region-sidebar-second {right:-0.8em;}
<?php endif;?>

<?php if(!empty($wklwiklmas['widthastablecell_footer_head_menu'])):?>
	.s-main-menu .content > ul,.subfooter-menu .content > ul {display:table;width:100%;padding: 0 0.5em;box-sizing:padding-box;}
	.s-main-menu .content > ul > li ,.subfooter-menu .content > ul > li {display:table-cell;text-align:center;}
<?php endif;?>

<?php if (!empty($wklwiklmas['region_sadow'])):?>
	.page-all-content, .region-subfooter, .region-sfooter {box-shadow:0 0 1em -0.5em black;}
<?php endif;?>