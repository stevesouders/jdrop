<?php

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

require_once('secrets.inc');
function hashForKey($authkey, $provider) {
  return md5("$authkey-$provider-" . SALT);
}

?>
