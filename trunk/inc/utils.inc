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
    <li> sign in to Jdrop </li>
    <li> install any of the <a href="apps">apps</a> that use Jdrop</li>
    <li> run the app and save data to Jdrop</li>
  </ul>
  <h3> On your desktop or laptop:</h3>
  <ul>
    <li> sign in to Jdrop </li>
    <li> view the <a href="myjson">JSON data</a> that you generated</li>
  </ul>
<?php }


// Simple logging/debugging function.
function dprint($msg) {
	error_log("DPRINT: $msg\n");
}


function insertStyles() {}
function insertHeader($title) {}

?>
