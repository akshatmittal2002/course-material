use assignment08;

delimiter ||
create procedure tt_violation()
begin
	select distinct cwsl1.roll_number, cwsl1.stud_name, cwsl1.cid as cid1, cwsl2.cid as cid2
    from cwsl as cwsl1
    join cwsl as cwsl2
    on ((cwsl1.roll_number = cwsl2.roll_number)
    and (cwsl1.cid < cwsl2.cid))
    where (cwsl1.cid,cwsl2.cid) in (
		select ett1.cid,ett2.cid
		from ett as ett1
		join ett as ett2
		on ett1.cid <> ett2.cid
		where ((ett1.exam_date = ett2.exam_date)
		and (((ett1.start_time <= ett2.start_time) and (ett1.end_time >= ett2.end_time))
        or ((ett2.start_time <= ett1.start_time) and (ett2.end_time >= ett1.end_time))
        or ((ett1.start_time >= ett2.start_time) and (ett2.end_time <= ett1.end_time) and (ett1.start_time <= ett2.end_time))
		or ((ett2.start_time >= ett1.start_time) and (ett1.end_time <= ett2.end_time) and (ett2.start_time <= ett1.end_time))))
	);
end ||
delimiter ;
