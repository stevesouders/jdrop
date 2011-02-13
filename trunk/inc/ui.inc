<?php

function ui_head($title) { // in lieu of decent templating
	$authkey = getAuthkey(true);
	$welcome = ( $authkey ? "<span id=welcomemsg style='font-style: italic; margin-right: 20px;'>" . getWelcome($authkey) . "</span> " : "" );
  $logout = ($authkey ? '&nbsp;|&nbsp;<a href="logout">logout</a>' : '');

  print "<!DOCTYPE html><html><head>";
  print "<title>Jdrop | $title</title>";
  print "<meta http-equiv='content-type' content='text/html; charset=UTF-8' />";
  print "<meta name='keywords' content='mobile json phone developer software development debug performance' />";
  print "<link rel='stylesheet' href='/style.css' type='text/css' />";
  print "</head><body>";
  print "<header><hgroup><h1>Jdrop</h1><h2>JSON in the cloud</h2></hgroup></header><nav>";
  print "some nav";
  print "</nav>";
  print "<article><h2>$title</h2>";
}

function ui_foot() {
  print "</article><footer><section>";
  print "the end";
  print "</section></footer></body></html>";
}

?>