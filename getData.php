<?php
class rempli{
 public $link='';
 function __construct($point, $niveau){
  $this->connect();
  $this->delete($point, $niveau);
  $this->storeInDB($point, $niveau);
 }

 function connect(){
  $this->link = mysqli_connect('localhost','site','site') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'site') or die('Cannot select the DB');
 }

 function delete($point, $niveau){
   $this->link = mysqli_connect('localhost','site','site') or die('Cannot connect to the DB');
   $del = "DELETE FROM rempli WHERE point = '".$point."'";
   $result1 = mysqli_query($this->link,$del) or die('Errant query:  '.$del);
 }

 function storeInDB($point, $niveau){
   $this->link = mysqli_connect('localhost','site','site') or die('Cannot connect to the DB');
  $query = "INSERT INTO rempli (point, niveau, date) VALUES ('".$point."', '".$niveau."',now())";
  $result2 = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }

}
if($_GET['point'] != '' and  $_GET['niveau'] != ''){
 $rempli=new rempli($_GET['point'],$_GET['niveau']);
}


?>
