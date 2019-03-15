<?php


require 'Mapspot.php';
if (isset($_POST["lat"])&&isset($_POST["lon"])) {
	$lat=$_POST["lat"];
	$lon=$_POST["lon"];
	$Map_Spot= new Leaflet_Map_Spot($lat,$lon);
	$Map_Spot->Inf_Match();
	$Map_Spot->Weboutput_Tables();
}
else{
	echo "<script>alert(\"net connection error \");</script>";
}
?>