<?php

function insertAbout() { ?>
  <p>
    Jdrop provides a place to store JSON data in the cloud.
    The initial application is for storing performance data gathered from mobile devices.
    It's hard to analyze large amounts of information (HTTP waterfall charts, HTTP headers, document source, etc.) on a mobile device.
    Jdrop lets you <em>gather</em> this data on the mobile device but <em>analyze</em> it remotely on a larger screen.
  </p>
<?php }


function insertHowTo() { ?>
  <h2>How to use Jdrop...</h2>
  <h3> On your mobile device:</h3>
  <ul>
    <li> Sign in to Jdrop </li>
    <li> install any of the <a href="apps">apps</a> that use Jdrop</li>
    <li> run the app and save data to Jdrop</li>
  </ul>
  <h3> On your desktop or laptop:</h3>
  <ul>
    <li> Sign in to Jdrop </li>
    <li> view the <a href="myjson">JSON data</a> that you generated</li>
  </ul>
  <p>
   Checkout the <a href="example">example use case</a> for screenshots and more information.
  </p>
<?php }


// Simple logging/debugging function.
function dprint($msg) {
	error_log("DPRINT: $msg\n");
}


function insertStyles() {}
function insertHeader($title) {}

?>
