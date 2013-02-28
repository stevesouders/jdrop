<?php
/*
Copyright 2011 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

See the source code here:
     http://code.google.com/p/jdrop/
*/

ini_set('display_errors', 'stderr');
header("Content-type:text/html");

function ui_head($title) { // in lieu of decent templating
  print "<!DOCTYPE html><html>\n<head>\n";
  print "<title>Jdrop | $title</title>\n";
  print "<meta http-equiv='content-type' content='text/html; charset=UTF-8' />\n";
  print "<meta name='viewport' content='width=device-width,initial-scale=1.0'>\n";
  print "<meta name='keywords' content='mobile json phone developer software development debug performance' />\n";
  ui_style();
  print "</head>\n<body>\n";
  print "<header><hgroup><h1>Jdrop</h1><h2>JSON in the cloud</h2></hgroup></header>\n<nav>\n<ul>";
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
	$username = getUsername();

	if ( !$username && strpos($_SERVER["REQUEST_URI"], "/public") ) {
		// show nothing
	}
	else {
		print "<section id='account' class='logged";
		if ($username) {
			print "in'>Logged in as $username | ";
			print "<a href='/logout'>Logout</a>";
		} else {
			print "out'><h3>Sign in with an online account</h3><ul>";
			foreach (array(
						   'Twitter'=>'twitter',
						   'Google'=>'google'
						   ) as $name=>$type) {
				print "<li><a href='oauth/$type' class='$type login'>$name</a></li>";
			}
			print "</ul><p>If you don't want to login,<br/>you can also <a href='/public'>view public JSON</a></p>";
		}
		print "</section>";
	}
}

function ui_foot() {
  print "</article><footer><section>";
  print "Jdrop &copy; 2011";
  print "</section></footer></body></html>";
}

?>
