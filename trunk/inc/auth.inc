<?php
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
