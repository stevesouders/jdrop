<?php
require_once("inc/auth.inc");
$bAuth = ( getAuthKey() ? 1 : 0 );

if ( array_key_exists("jsonp", $_GET) ) {
	$func = $_GET["jsonp"];
	echo "$func($bAuth);\n";
}
else {
	echo "RemoteResults = RemoteResults || {};\nRemoteResults.bAuth = $bAuth;\n";
}
?>

