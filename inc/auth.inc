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

require_once('utils.inc');

// return the "username" based on cookies
function getAuthkey() {
	if (array_key_exists("user", $_COOKIE)) {
		if ($keyAndHash = $_COOKIE["user"]) {
			list($key, $provider, $hash) = split("\t", $keyAndHash, 3);
			if (hashForKey($key, $provider) == $hash) {
				return "$key ($provider)";
			}
		}
	}
	return "";
}


// return the "username" based on cookies
function getUsername() {
  //return 'souders';
	if (array_key_exists("user", $_COOKIE)) {
		if ($keyAndHash = $_COOKIE["user"]) {
			list($key, $provider, $hash) = split("\t", $keyAndHash, 3);
			if (hashForKey($key, $provider) == $hash) {
				return $key;
			}
		}
  }
	return "";
}


function setAuthkey($authkey, $provider) {
  $hash = hashForKey($authkey, $provider);
	setcookie("user", "$authkey\t$provider\t$hash", 0, "/");
}


function clearAuthkey() {
	setcookie("user", "", 0, "/");
}

// secrets.inc is NOT in SVN so let's help people during installation if they forgot to configure it
if ( !include_once('secrets.inc') ) {
	dprint("inc/secrets.inc is missing");
	echo "inc/secrets.inc is missing\n";
	exit();
}

function hashForKey($authkey, $provider) {
  return md5("$authkey-$provider-" . SALT);
}


$ghAuthUsers = array("jamespearce (Twitter)" => 1,
					 "souders (Twitter)" => 1,
					 "stevesoudersorg (Google)" => 1
					 );

function authUser() {
	global $ghAuthUsers;
	return ( getAuthkey() && array_key_exists(getAuthkey(), $ghAuthUsers) );
}

/* add this if you want to restrict the site based on authkey
if ( !authUser() &&
	 ! ( $_SERVER["REQUEST_URI"] === "/" ||
		 $_SERVER["REQUEST_URI"] === "/home" ||
		 0 === strpos($_SERVER["REQUEST_URI"], "/oauth") ||
		 0 === strpos($_SERVER["REQUEST_URI"], "/dev") )
	 ) {
	header("HTTP/1.0 401 Unauthorized");
	exit();
}
*/
?>
