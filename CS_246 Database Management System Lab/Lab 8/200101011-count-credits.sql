use assignment08;

delimiter ||
create procedure count_credits()
begin
	select roll_number,stud_name,total_credits
    from (
		select roll_number,stud_name,sum(credits) as total_credits
        from cwsl
        join cc
        on cwsl.cid = cc.cid
        group by roll_number) as temp
	where total_credits > 40;
end ||
delimiter ;