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

require_once("inc/auth.inc");
require_once("inc/utils.inc");
require_once("inc/db.inc");
require_once("inc/uaparser.inc");

$gAuthkey = getAuthkey();

if ( !isset($gbViewPublic) ) {
	$gbViewPublic = false;
}

if ( $gAuthkey || $gbViewPublic ) {
	$pApp = ( array_key_exists("app", $_GET) ? $_GET["app"] : "" );
	$pSite = ( array_key_exists("site", $_GET) ? $_GET["site"] : "" );
	$pUrl = ( array_key_exists("url", $_GET) ? $_GET["url"] : "" );
	$pBrowser = ( array_key_exists("browser", $_GET) ? $_GET["browser"] : "" );

	$aConds = array();
	if ( $pApp ) {
		array_push($aConds, "appname like '%$pApp%'");
	}
	if ( $pSite ) {
		array_push($aConds, "title like '%$pSite%'");
	}
	if ( $pUrl ) {
		array_push($aConds, "referer like '%$pBrowser%'");
	}
	if ( $pBrowser ) {
		array_push($aConds, "browser like '%$pBrowser%'");
	}

	$sConds = "";
	$sDisplay = "none";
	if ( count($aConds) ) {
		$sConds = "and (" . implode(" and ", $aConds) . ")";
		$sDisplay = "block";
	}

	echo <<<OUTPUT
<style>
.label { font-weight: bold; text-align: right; }
#search TD { padding: 2px 4px; font-size: 0.9em; }
#results TH { border-bottom: 1px solid #000; padding: 12px 4px; }
#results TD { border-bottom: 1px solid #CCC; padding: 2px 8px; font-size: 0.9em; }
#filterbtn { font-family: "HelveticaNeue-Medium", "Helvetica Neue", Helvetica, Arial, sans-serif; font-weight: bold; font-size: 16px; text-decoration: none; border: 1px solid #C66300; color: #FFF; padding: 2px 4px; background: #C66300; }
#filterbtn:hover { background: #E70; border: 1px solid #E03105; }
.jsonlink { background: #F9F9F9; padding: 0 2px; border: 1px solid #D6C8BA; text-decoration: none; color: #630; font-size: 0.9em; margin: 0 0.2em 0 0.2em; }
.jsonlink:hover { background: #C66300; color: #FFF; }
.removelink { background: #F9F9F9; padding: 0 2px; border: 1px solid #D6C8BA; text-decoration: none; color: #900; font-size: 0.9em; margin: 0 0.2em 0 0.2em; }
.removelink:hover { background: #900; color: #FFF; }
</style>

<table cellpadding=0 cellspacing=0 border=0 style="margin-bottom: 0; font-size: 0.9em;">
 <tr>
   <td style="vertical-align: top;"> <a id=filterbtn href="toggle" onclick="toggleSearchForm();return false;">filter &rsaquo;&rsaquo;</a> </td>
   <td> 
<div id=searchform style="display: $sDisplay; border: 1px solid #AAA; padding: 4px; margin-left: 8px; margin-bottom: 20px;">
<form>
<table id=search cellpadding=0 cellspacing=0 border=0>
  <tr> <td class=label>App:</td> <td><input type=text size=35 name=app value="$pApp"></td> <td></td> </tr>
  <tr> <td class=label>Website:</td> <td><input type=text size=35 name=site value="$pSite"></td> <td></td> </tr>
  <tr> <td class=label>URL:</td> <td><input type=text size=35 name=url value="$pUrl"></td> <td></td> </tr>
  <tr> <td class=label>Browser:</td> <td><input type=text size=35 name=browser value="$pBrowser"></td> <td style="vertical-align: top;"><input type=submit value="Filter"></td> </tr>
</table>
</form>
</div>
  </td>
 </tr>
</table>
OUTPUT;

	$query = "select dataid, public, createDate, referer, appname, title, browser, version, summary from data where " .
		( $gbViewPublic ? "public=1 " : "authkey='$gAuthkey' " ) .
		"$sConds order by createDate desc limit 1000;";
	$result = doQuery($query);

	if ( $result ) {
		$bFirst = true;
		while ( $row = mysql_fetch_assoc($result) ) {
			if ( $bFirst ) {
				$bFirst = false;
				echo "<div style='width: 1200px;'>\n" .
					"<table id=results class=tablesort cellpadding=0 cellspacing=0 border=0>\n" .
					"<tr> <th>Date</th> <th>JSON</th> " .
					( $gbViewPublic ? "" : "<th>Public</th> " ) .
					"<th>App</th> <th style='width: 300px;'>Website</th> <th>Summary</th> <th>Browser</th> </tr>\n";
			}
			$dataid = $row['dataid'];
			$checked = ( $row['public'] ? " checked" : "" );
			$date = $row['createDate'];
			$date = date("n/j/Y H:i", $date);
			$url = $row['referer'];
			$appname = $row['appname'];
			$version = $row['version'];
			$version = ( $version ? " $version" : "" );
			$summary = $row['summary'];
			$browser = parseUserAgent($row['browser']);
			$title = $row['title'];
			$title = substr(( $title ? $title : $url ), 0, 64);
			echo "  <tr id=$dataid> <td><nobr>$date</nobr></td> " .
				"<td style='text-align: center;'><a class=jsonlink href='view?id=$dataid'>view</a> <a class=jsonlink href='export?id=$dataid'>export</a> " .
				( $gbViewPublic ? "" : "<a href='#' onclick='doDelete($dataid); return false' class=removelink style='font-weight: bold;' title='remove'>X</a></td> " ) .
				( $gbViewPublic ? "" : "<td style='text-align: center;'><input type=checkbox name=public$checked onclick='togglePublic($dataid, \"$checked\", this)'></td> " ) .
				"<td><nobr>$appname$version</nobr></td> <td><a href='$url'>$title</a></td> <td>$summary</td> <td><nobr>$browser</nobr></td>" .
				" </tr>\n";
		}
		mysql_free_result($result);
		if ( ! $bFirst ) {
			echo <<<OUTPUT
</table>
</div> <!-- wide div -->

<script type="text/javascript">
function toggleSearchForm() {
	var form = document.getElementById('searchform');
	var bShow = ( "none" === form.style.display );
	form.style.display = ( bShow ? "block" : "none" );

	var filterbtn = document.getElementById('filterbtn');
	filterbtn.innerHTML = ( bShow ? "filter &lsaquo;&lsaquo;" : "filter &rsaquo;&rsaquo;" );	
}

function togglePublic(dataid, bPublicNow, elem) {
	// don't bother to check if they're making they're making it private
	if ( !bPublicNow && !confirm("Are you sure you want to make this data public to the world?") ) {
		elem.checked = false;
		return;
	}

	new Image().src = "http://jdrop.org/publish?id=" + dataid + "&pub=" + ( bPublicNow ? "0" : "1" );
}

function doDelete(dataid) {
	(new Image()).src = "remove?id=" + dataid;
	var tr = document.getElementById(dataid);
	if ( tr ) {
		tr.style.display = "none";
	}
}

var script = document.createElement('script');
script.src = "tablesort.js";
script.onload = function() { TS.init(); };
document.getElementsByTagName('head')[0].appendChild(script);
</script>

OUTPUT;
		}
		else if ( $sConds ) {
			echo "<p>nothing found</p>\n\n";
		}
		else {
			echo "<p>You don't have any JSON (yet). Check out the <a href='apps'>apps</a>.</p>\n\n";
		}
	}
}
?>


