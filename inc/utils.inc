<?php

function insertStyles() {
	echo <<<OUTPUT
<style>
BODY { font-family: Arial, Sans-Serif; font-size: 16px; width: 900px; line-height: 1.2em; color: #333; }
H1 { font-size: 48px; margin-top: 0; }
.warning { color: #700; }
.ahover { text-decoration: none; }
.ahover:hover { text-decoration: underline; }
.ahoverborder { text-decoration: none; border: 1px solid #FFF; padding: 0 2px 0 2px; }
.ahoverborder:hover { border: 1px solid; }
</style>

OUTPUT;
}


function insertHeader($title) {
	$username = getUsername();
	$welcome = ( $username ? "<span id=welcomemsg style='font-style: italic; margin-right: 20px;'>" . getWelcome($username) . "</span> " : "" );
  $logout = ($username ? '&nbsp;|&nbsp;<a href="logout">logout</a>' : '');

	echo <<<OUTPUT
<div style="float: right; font-size: 0.9em;">
$welcome
<a href="home">home</a>
&nbsp;|&nbsp;
<a href="myjson">myJSON</a>
&nbsp;|&nbsp;
<a href="apps">apps</a>
&nbsp;|&nbsp;
<a href="about">about</a>
$logout</div>
<h1><img src="images/logo-59x59.png" width=59 height=59><nobr>$title</nobr></h1>

OUTPUT;
}


function getWelcome($username) {
	$aGreetings = array("hey", "yo", "rock on", "welcome", "hi", "hola", "peace", "surf's up", "greetings",
						"g'day", "cheers", "hello");
	return $aGreetings[rand(0, count($aGreetings)-1)] . " $username";
}


function insertAbout() {
	echo <<<OUTPUT
<p style="margin-top: 20px;">
JDrop provides a place to store JSON data in the cloud.
The initial application is for storing performance data gathered from mobile devices.
It's hard to analyze large amounts of information (HTTP waterfall charts, HTTP headers, document source, etc.) on a mobile device.
JDrop lets you <em>gather</em> this data on the mobile device but <em>analyze</em> it remotely on a larger screen.
</p>
OUTPUT;
}


function insertHowTo() {
    echo <<<OUTPUT
<style>
OL > LI { margin-bottom: 8px; }
LI { line-height: 1.4em; }
</style>

<div style="font-weight: bold; margin-top: 30px; font-size: 1.3em;">
How to use JDrop:
</div>

<ul style="list-style-type: none;">
  <li> <b>On your mobile device:</b>
    <ul style="margin-top: 0;">
      <li> <a href="home">sign in to JDrop</a>
      <li> install any of the <a href="apps">apps</a> that use JDrop
      <li> run the app and save data to JDrop
    </ul>
  <li style="margin-top: 8px;"> <b>On your desktop or laptop:</b>
    <ul style="margin-top: 0;">
      <li> <a href="home">sign in to JDrop</a>
      <li> view the <a href="myjson">JSON data</a> that you generated
    </ul>
</ul>

<p style="margin-top: 30px;">
Checkout the <a href="example">example use case</a> for screenshots and more information.
</p>
OUTPUT;
}


function insertLoginForm() {
	echo <<<OUTPUT
<div style="margin-top: 40px;">
<strong>Sign in with an online account:</strong>
<div style="margin: 8px 0 8px 20px;">
<a href='oauth/twitter' class=warning alt="Login with Twitter"><img src="images/twitter.png" style="margin:4px;border: 0;vertical-align:middle; margin-right: 0;" width=32 height=32></a>
<a href='oauth/twitter' class=warning alt="Login with Twitter">Twitter</a>
&nbsp;&nbsp;&nbsp;
<a href='oauth/google' class=warning alt="Login with Google"><img src="images/google.png" style="margin:4px;border: 0;vertical-align:middle; margin-right: 0;" width=32 height=32></a>
<a href='oauth/google' class=warning alt="Login with Google">Google</a>
</div>
</div>
OUTPUT;
}


//function insertLoginForm() {
//	$authkey = getAuthkey();
//	$loginmsg = ( $authkey ? "You're logged in as \"$authkey\"." : "You're not logged in." );
//
//	echo <<<OUTPUT
//<script>
//function doLogin() {
//	var username = document.getElementById("u").value;
//	if ( username.length > 32 ) {
//		alert("Username must be less than 32 characters.");
//		return;
//	}
//
//	createCookie("a", username);
//	if ( username ) {
//		document.getElementById('loginmsg').innerHTML = "You're logged in as \"" + username + "\".";
//		document.getElementById('welcomemsg').innerHTML = "hey " + username;
//	}
//}
//
//function createCookie(name, value, days) {
//	if (days) {
//		var date = new Date();
//		date.setTime(date.getTime()+(days*24*60*60*1000));
//		var expires = "; expires="+date.toGMTString();
//	}
//	else {
//		var expires = "";
//	}
//	window.document.cookie = name + "=" + value + expires + "; path=/";
//}
//
//
//function readCookie(name) {
//	var nameEQ = name + "=";
//	var ca = window.document.cookie.split(';');
//	for( var i=0; i < ca.length; i++) {
//		var c = ca[i];
//		while ( c.charAt(0)==' ' ) {
//			c = c.substring(1,c.length);
//		}
//		if ( c.indexOf(nameEQ) == 0 ) {
//			return c.substring(nameEQ.length,c.length);
//		}
//	}
//	return null;
//}
//</script>
//
//<div style="float: right; margin: 0 0 8px 8px; border: 2px solid #73B5DE; padding: 8px;">
//<form name=login id=login onsubmit="doLogin(); return false;">
//<table cellpadding=0 cellspacing=0 border=0>
//<tr>
//  <td colspan=3 id=loginmsg style='font-weight: bold; padding-bottom: 8px;'>$loginmsg</td>
//<tr>
//  <td>Username:</td>
//  <td style="padding-left: 8px;"><input type=text size=10 name=u id=u value='$authkey'></td>
//  <td style="padding-left: 8px;"><input type=submit value='"Login"'>
//</tr>
//</table>
//</form>
//<p style="font-style: italic; font-size: 0.9em; width: 300px; margin-bottom: 0;">
//OK, I know this isn't a real login form.
//I haven't incorporated OAuth or anything yet.
//For now, just enter a string that can be used to sync the results on your phone with this website.
//Something like "bigdog" or "Steve17".
//I'll do login soon - just avoid confidential info until then.
//</p>
//</div>
//OUTPUT;
//}
//
//
//// Use a dev version of the database tables if "dev/" is in the path.
//$gbDev = ( strpos(getcwd(), "/dev/") || strpos(getcwd(), "/trunk") );
//
//// Logic to shorten a URL while retaining readability.
//function shortenUrl($url) {
//	$max = 48;
//
//	if ( strlen($url) < $max ) {
//		return $url;
//	}
//
//	// Strip the querystring.
//	$iQueryString = strpos($url, "?");
//	if ( $iQueryString ) {
//		$url = substr($url, 0, $iQueryString);
//	}
//
//	if ( strlen($url) < $max ) {
//		return $url;
//	}
//
//	$iDoubleSlash = strpos($url, "//");
//	$iFirstSlash = strpos($url, "/", $iDoubleSlash+2);
//	$iLastSlash = strrpos($url, "/");
//
//	$sHostname = substr($url, 0, $iFirstSlash); // does NOT include trailing slash
//	$sPath = substr($url, $iFirstSlash, $iLastSlash);
//	$sFilename = substr($url, $iLastSlash);
//
//	$url = $sHostname . "/..." . $sFilename;
//	if ( strlen($url) < $max ) {
//		// Add as much of the path as possible.
//		$url = str_replace("/...", "/" . substr($sPath, 1, $max - strlen($url)) . "...", $url);
//		return $url;
//	}
//
//	$url = substr($url, 0, $max-3) . "...";
//
//	return $url;
//}


// Simple logging/debugging function.
function dprint($msg) {
	error_log("DPRINT: $msg\n");
}

?>