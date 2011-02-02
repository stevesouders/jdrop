<?php
require_once("utils.inc");

$gMysqlServer = "db.jdrop.org";
$gMysqlDb = "jdrop";
$gMysqlUsername = "jdropadmin";
$gMysqlPassword = "ENTER_PASSWORD_HERE";
$gDataTable = "data";
$gAppsTable = "apps";

// Use a dev version of the database tables if "dev/" is in the path.
$gbDev = ( strpos(getcwd(), "/dev/") || strpos(getcwd(), "/trunk") );
if ( $gbDev ) {
	// TODO - Do this after we launch.
	//$gDataTable .= "dev";
	//$gAppsTable .= "dev";
}


function doSimpleCommand($cmd) {
	global $gMysqlServer, $gMysqlDb, $gMysqlUsername, $gMysqlPassword;

	$value = NULL;
	$link = mysql_connect($gMysqlServer, $gMysqlUsername, $gMysqlPassword);
	if ( mysql_select_db($gMysqlDb) ) {
		//error_log("doSimpleCommand: $cmd");
		$result = mysql_query($cmd, $link);
		if ( ! $result ) {
			dprint("ERROR in doSimpleCommand: '" . mysql_error() . "' for command: " . $cmd);
		}
	}
}


function doQuery($query) {
	global $gMysqlServer, $gMysqlDb, $gMysqlUsername, $gMysqlPassword;

	$value = NULL;
	$link = mysql_connect($gMysqlServer, $gMysqlUsername, $gMysqlPassword);
	if ( mysql_select_db($gMysqlDb) ) {
		//error_log("doQuery: $query");
		$result = mysql_query($query, $link);
		if ( ! $result ) {
			dprint("ERROR in doQuery: '" . mysql_error() . "' for query: " . $query);
		}
		return $result;
	}

	return null;
}


// return the first row
function doRowQuery($query) {
	$result = doQuery($query);
	if ( $result ) {
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
	}

	return $row;
}


// return the first value from the first row
function doSimpleQuery($query) {
	$result = doQuery($query);

	$value = null;
	if ( $result ) {
		$row = mysql_fetch_assoc($result);
		if ( $row ) {
			$aKeys = array_keys($row);
			$value = $row[$aKeys[0]];
		}
		mysql_free_result($result);
	}

	return $value;
}


function createTables() {
	global $gDataTable, $gAppsTable;

	if ( ! tableExists($gDataTable) ) {
		$command = "create table $gDataTable (" .
			"dataid int unsigned not null auto_increment" .
			", authkey varchar (32) not null" .
			", createDate int(10) unsigned not null" .
			", referer varchar (255) not null" .
			", browser varchar (255) not null" .
			", title varchar (255) not null" .
			", appname varchar (255) not null" .
			", version varchar (32) not null" .
			", summary varchar (255) not null" .
			", json mediumblob not null" .   // 16M
			", primary key (dataid)" .
			");";
		doSimpleCommand($command);
	}

	if ( ! tableExists("apps") ) {
		$command = "create table apps (" .
			"appid int unsigned not null auto_increment" .
			", appname varchar (255) not null" .
			", jsurl text not null" .
			", callback varchar (255) not null" .
			", format varchar (32) not null" .
			", formatkey varchar (32) not null" .
			", primary key (appid)" .
			", unique key (appname)" .
			");";
		doSimpleCommand($command);
	}
}


function tableExists($tablename) {
	return ( $tablename == doSimpleQuery("show tables like '$tablename';") );
}


// Escape ' and \ characters before inserting strings into MySQL.
function mysqlEscape($text) {
	return str_replace("'", "\\'", str_replace("\\", "\\\\", $text));
}

?>
