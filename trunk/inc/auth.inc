<?php

// return the "username" based on cookies
function getAuthkey($name_only) {
	if (array_key_exists("user", $_COOKIE)) {
    if ($keyAndHash = $_COOKIE["user"]) {
      list($key, $provider, $hash) = split("\t", $keyAndHash, 3);
      if (hashForKey($key, $provider) == $hash) {
        if ($name_only) {
          return $key;
        }
        return "$key ($provider)";
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


function hashForKey($authkey, $provider) {
  return md5("$authkey-$provider-thisistheyearofthemobileweb");
}

?>
