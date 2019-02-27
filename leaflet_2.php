<?php
$lat=$_POST["lat"];
$lon=$_POST["lon"];
if (isset($_POST["lat"])&&isset($_POST["lon"])) {
	$lat=$_POST["lat"];
	$lon=$_POST["lon"];
	switch ("$lat,$lon") {
		case '-15.601,-47.713':
			echo "<img src=\"leaflet_src/Brasilia\" alt=\"Brasilia\" />";
			break;
		case '60.1389,-1.1847':
			echo "<img src=\"leaflet_src/Lerwick\" alt=\"Lerwick\" />";
			break;
		case '-89.983,-24.799':
			echo "<img src=\"leaflet_src/South_Pole\" alt=\"South_Pole\" />";
			break;
		case '43.73,-96.62':
			echo "<img src=\"leaflet_src/Sioux_Falls\" alt=\"Sioux_Falls\" />";
			break;
		case '22.7903,5.5292':
			echo "<img src=\"leaflet_src/Tamanrasset\" alt=\"Tamanrasset\" />";
			break;
		default:
			echo "<script>alert(\"somthing wrong \");</script>";
			break;
	}
}
else{
	echo "<script>alert(\"net connection error \");</script>";
}
?>