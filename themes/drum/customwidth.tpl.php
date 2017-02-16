.region-shead,.region-shead-menu,.page-all-content,.region-subfooter,.region-sfooter {/*width:97.5em;*/max-width:<?php echo $widthmas['maxcontentwidth'];?>;min-width:<?php echo $widthmas['mincontentwidth'];?>;margin:0 auto;}

.sidebar-second .region-content {margin: 0 <?php echo $widthmas['sidebarssize'];?> 0 0.8em;overflow:hidden;}
.sidebar-first .region-content {margin: 0 0.8em 0 <?php echo $widthmas['sidebarssize'];?>;overflow:hidden;}
.two-sidebars .region-content {margin:0 <?php echo $widthmas['sidebarssize'];?>;overflow:hidden;}
.region-sidebar-first, .region-sidebar-second {width:calc(<?php echo $widthmas['sidebarssize'];?> - 1em);}
.region-sidebar-first {float:left;position:relative;left:-0.8em;}
.region-sidebar-second {float:right;position:relative;right:-0.8em;}