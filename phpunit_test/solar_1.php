<?php
/**
 * 
 */
class Leaflet_Map_Spot
{
	public $lat;
	public $lon;
	public $Location;
	public $error_log;
	function __construct($latitude,$lontitude)
	{
		if (is_numeric($latitude)&&is_numeric($lontitude)&&$latitude>=-90&&$latitude<=90&&$lontitude>=-180&&$lontitude<=180) {
			$this->lat=$latitude;
			$this->lon=$lontitude;
		}
		else{
			$this->error_log="Wrong Input";
		}
	}
	function Inf_Match(){
		switch ("$this->lat,$this->lon") {
		case '-15.601,-47.713':
			$this->Location='Brasilia';
			break;
		case '60.1389,-1.1847':
			$this->Location='Lerwick';
			break;
		case '-89.983,-24.799':
			$this->Location='South_Pole';
			break;
		case '43.73,-96.62':
			$this->Location='Sioux_Falls';
			break;
		case '22.7903,5.5292':
			$this->Location='Tamanrasset';
			break;
		default:
			$this->error_log="Can't Match Any Spot In Database";
			break;
		}
	}
	function Weboutput(){
		if (isset($this->error_log)) {
			echo "<script>alert(\"$this->error_log\");</script>";
		}
		else{
			echo "<img src=\"leaflet_src/$this->Location\" alt=\"$this->Location\" />";
		}
	}
}
?>