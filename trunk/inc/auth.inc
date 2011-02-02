<?php

// return the "username" based on cookies
function getAuthkey() {
	return ( array_key_exists("a", $_COOKIE) ? $_COOKIE["a"] : "" );
}


function setAuthkey($authkey) {
	setcookie("a", $authkey, 0, "/");
}


function clearAuthkey() {
	setcookie("a", "", 0, "/");
}

?>
