<?php

ini_set('display_errors');
header("Content-type:text/html");

function ui_head($title) { // in lieu of decent templating
  print "<!DOCTYPE html><html><head>";
  print "<title>Jdrop | $title</title>";
  print "<meta http-equiv='content-type' content='text/html; charset=UTF-8' />";
  print "<meta name='keywords' content='mobile json phone developer software development debug performance' />";
  ui_style();
  print "</head><body>";
  print "<header><hgroup><h1>Jdrop</h1><h2>JSON in the cloud</h2></hgroup></header><nav><ul class=navlinks>";
  ui_nav();
  print "</ul></nav><article>";
  ui_account();
  print "<h2>$title</h2>";
}

function ui_style() {
  print "<link rel='stylesheet' href='style.css' type='text/css' />";
}

function ui_nav() {
  $here = $_SERVER['REQUEST_URI'];
  foreach (array(
    'Home'=>'home',
    'My JSON'=>'myjson',
    'Public'=>'public',
    'Apps'=>'apps',
    'About'=>'about'
  ) as $name=>$link) {
    print "<li><a" . (stripos($here, $link)===0?" class='active'":"") . " href='$link'>$name</a></li>";
  }

}

function ui_account() {
  print "<section id='account' class='logged";
  $username = getUsername();
  if ($username) {
    print "in'>Logged in as $username | ";
    print "<a href='/logout'>Logout</a>";
  } else {
    print "out'><h3>Sign in with an online account</h3><ul>";
    foreach (array(
      'Twitter'=>'twitter',
      'Google'=>'google'
    ) as $name=>$type) {
      print "<li><a href='oauth/twitter' class='$type login'>$name</a></li>";
    }
    print "</ul><p>If you don't want to login,<br/>you can also <a href='/public'>view public JSON</a></p>";
  }
  print "</section>";
}


function ui_foot() {
  print "</article><footer><section>";
  print "&copy; 2011";
  print "</section></footer></body></html>";
}

?>