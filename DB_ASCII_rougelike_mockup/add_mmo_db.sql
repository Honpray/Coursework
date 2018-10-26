--create mmo database
drop database if exists mmo;
create database mmo;
use mmo;

create table player (
  	playerid varchar(25) not null,
	password varchar(225) not null,
	loggedintime timestamp,
	roomid integer,
	health integer,
	positionx integer,
	positiony integer,
	online boolean,
	primary key (playerid)
);

create table item (
	itemid integer not null auto_increment,
	itemname varchar(25) not null,
	itemdescription varchar(128),
	primary key (itemid)
);

create table inventory (
	playerid varchar(25) not null,
	itemid integer not null,
	primary key (playerid, itemid)
);

create table room (
	roomid integer not null auto_increment,
	roomname varchar(25) not null,
	sizex integer,
	sizey integer,
	primary key (roomid)
);

create table roomcontents(
	roomid varchar(25) not null,
	itemid integer not null,
	itemx integer,
	itemy integer,
	primary key (roomid, itemid)
);

create view intheroom as 
select player.playerid, roomcontents.itemid
from player
inner join roomcontents on player.roomid = roomcontents.roomid;


insert into player values('test1',SHA('test1'),now(),1,100,FLOOR( 1 + RAND( ) *20 ),FLOOR( 1 + RAND( ) *50 ), false);
insert into player values('test2',SHA('test2'),now(),1,100,FLOOR( 1 + RAND( ) *20 ),FLOOR( 1 + RAND( ) *50 ), false);
insert into player values('test3',SHA('test3'),now(),1,100,FLOOR( 1 + RAND( ) *20 ),FLOOR( 1 + RAND( ) *50 ), true);

insert into item (itemname, itemdescription) values('sword','A steel sword.');
insert into item (itemname, itemdescription) values('wand', 'A wooden wand with magic power');
insert into item (itemname, itemdescription) values('potion','Recover 30 HP');

insert into inventory values ('test1', 1);
insert into inventory values ('test1', 3);

insert into room (roomname, sizex, sizey) values('Room_A',50,20);

insert into roomcontents values (1, 1, 10,10);
insert into roomcontents values (1, 2, 40,10);
insert into roomcontents values (1, 3, 30,15);


--Store Procedures

--Movements
DROP PROCEDURE if exists moveleft;
delimiter //
CREATE PROCEDURE moveleft (in player_id varchar(25),out x integer, out y integer)
BEGIN
update player set positionx = positionx - 1 where playerid = player_id;
select positionx into x from player where playerid = player_id;
select positiony into y from player where playerid = player_id;
END//
delimiter ;

DROP PROCEDURE if exists moveright;
delimiter //
CREATE PROCEDURE moveright (in player_id varchar(25),out x integer, out y integer)
BEGIN
update player set positionx = positionx + 1 where playerid = player_id;
select positionx into x from player where playerid = player_id;
select positiony into y from player where playerid = player_id;
END//
delimiter ;

DROP PROCEDURE if exists moveup;
delimiter //
CREATE PROCEDURE moveup (in player_id varchar(25),out x integer, out y integer)
BEGIN
update player set positiony = positiony - 1 where playerid = player_id;
select positionx into x from player where playerid = player_id;
select positiony into y from player where playerid = player_id;
END//
delimiter ;

DROP PROCEDURE if exists movedown;
delimiter //
CREATE PROCEDURE movedown (in player_id varchar(25),out x integer, out y integer)
BEGIN
update player set positiony = positiony + 1 where playerid = player_id;
select positionx into x from player where playerid = player_id;
select positiony into y from player where playerid = player_id;
END//
delimiter ;

--at the beginning of game
DROP PROCEDURE if exists get_info;
delimiter //
CREATE PROCEDURE get_info (in player_id varchar(25),out time timestamp, out hp integer, out room_name varchar(25), out x integer, out y integer)
BEGIN
	select health into hp from player where playerid = player_id;
	select roomname into room_name from room,player where player.roomid = room.roomid and playerid = player_id;
	select loggedintime into time from player where playerid = player_id;
	select positionx into x from player where playerid = player_id;
	select positiony into y from player where playerid = player_id;
	update player set loggedintime = now() where playerid = player_id;
	update player set online = true where playerid = player_id;
END//
delimiter ;

--displaying items in current room
DROP PROCEDURE if exists displayitem;
delimiter //
CREATE PROCEDURE displayitem (in player_id varchar(25))
BEGIN
	select distinct itemname, itemx, itemy from item, roomcontents, player where item.itemid = roomcontents.itemid and roomcontents.roomid = player.roomid and playerid = player_id; 

	-- select itemname into name from item where itemid in (select itemid from roomcontents where roomid in (select roomid from player where playerid = player_id)); 
	-- select itemx into x from roomcontents where itemid in (select itemid from roomcontents where roomid in (select roomid from player where playerid = player_id));
	-- select itemy into y from roomcontents where itemid in (select itemid from roomcontents where roomid in (select roomid from player where playerid = player_id));
END//
delimiter ;

--if player overlap with the coordinate of item
DROP PROCEDURE if exists pickupitem;
delimiter //
CREATE PROCEDURE pickupitem (in player_id varchar(25), in item_id integer)
BEGIN
	start transaction;
	insert into inventory values(player_id, item_id);
	delete from roomcontents where itemid = item_id;
	commit;
END//
delimiter ;

DROP PROCEDURE if exists showplayers;
delimiter //
CREATE PROCEDURE showplayers(in player_id varchar(25))
BEGIN
	select playerid, positionx, positiony from player where online = 1 and playerid != player_id and roomid in (select roomid from player where playerid = player_id);

END//
delimiter ;



ALTER TABLE player ADD CONSTRAINT FK_player_roomid foreign key (roomid) references room(roomid);




