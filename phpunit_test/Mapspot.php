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
	function __construct($latitude,$lontitude)//create a mapspot by lat and lon
	{
		if (is_numeric($latitude)&&is_numeric($lontitude)&&$latitude>=-90&&$latitude<=90&&$lontitude>=-180&&$lontitude<=180) {
			$this->lat=$latitude;
			$this->lon=$lontitude;
		}
		else{
			$this->error_log="Error:Wrong Input";
		}
	}
	function Inf_Match(){//match mapspot 
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
			$this->error_log="Error:Can't Match Any Spot In Database";
			break;
		}
	}
	function Weboutput_Figures(){//output figures
		if (isset($this->error_log)) {
			echo "<script>alert(\"$this->error_log\");</script>";
		}
		else{
			echo "<img src=\"leaflet_src/$this->Location\" alt=\"$this->Location\" />";//path to figures
		}
	}
	function Weboutput_Tables(){//output tables
		require 'solardb.php';
		$dblink= new mysqli($ip,$account,$pass,$solar_db);
		if (!$dblink) {
    		$this->error_log="Error:Unable to connect to MySQL";//connect failed
		}
		else{
			$sql_col="show columns from ghi_".$this->Location;
			$res_col=$dblink->query($sql_col);
			if ($res_col->num_rows==0) {
				$this->error_log="Error:Table ghi_$this->Location connection failed!";//connect to table failed
			}
		}
		if (isset($this->error_log)) {
			echo "<script>alert(\"$this->error_log\");</script>";
			exit;
		}
		else{//nothing failed
			$Table_header="<caption class=\"text-left text-indented\" >$this->Location</caption><table border=\"1\"><tr>";//table header
			for ($i=0; $i <$res_col->num_rows; $i++) { 
				$columns[$i]=$res_col->fetch_row()[0];
				$Table_header=$Table_header."<th>$columns[$i]</th>";//get columns names
			}
			$Table_header=$Table_header."</tr>";
			echo "$Table_header";
			$sql_inf="select * from ghi_".$this->Location." limit 1000";//limit 1000 rows for now
			$res_inf=$dblink->query($sql_inf);
			for ($i=0; $i <$res_inf->num_rows; $i++) { 
				$Table_row="<tr>";
				$res_inf_row=$res_inf->fetch_row();
				for ($j=0; $j < count($res_inf_row); $j++) { 
					$Table_row=$Table_row."<td>$res_inf_row[$j]</td>";//generate table rows
				}
				$Table_row=$Table_row."</tr>";
				echo "$Table_row";
			}
			echo "</table>";
			
		}
		$dblink->close();
	}
}
?>