- measured against human holding tapemeasure above strawberry canopy. 
- utilized xm125 radar. 
- data includes raw and filtered(ewma on a median of 3 values)
- invalid value does not affect filter
- invalid value from raw is stored as -1

logfile rows formatted as 
{frame_id},{addr},{retcode},{distances},{raw_mm},{filtered_mm},{filtered_in},{p0_str},{tnow},{height_level}

data format stationary beds
bed<num>/stationary_<inch abv gnd(12,16,20)>_<pt on bed(1,2,3)>.txt

data format indoor ground
ground/stationary_<inch abv gnd>.txt