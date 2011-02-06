<?php

// return the "username" based on cookies
function getAuthkey() {
	if (array_key_exists("user", $_COOKIE)) {
    if ($keyAndHash = $_COOKIE["user"]) {
      list($key, $hash) = split("@", $keyAndHash, 2);
      if (hashForKey($key) == $hash) {
        return $key;
      }
    }
  }
  return "";
}


function setAuthkey($authkey) {
  $hash = hashForKey($authkey);
	setcookie("user", "$authkey@$hash", 0, "/");
}


function clearAuthkey() {
	setcookie("user", "", 0, "/");
}


function hashForKey($authkey) {
  return substr(md5("$authkey-thisistheyearofthemobileweb"), 0, 8);
}

?>
