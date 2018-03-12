
$fs = 0.7;

wheelSize = 13;

playLooseFit = 0.2;

trackWidth = 10;
trackThickness = 0.7;
trackTeethSpacing = (wheelSize * 6.2831) / 13;

trackTeethHeight = 1.5;	
trackTeethBaseWidth = 1.5;	
trackTeethTopWidth = 0.6;

trackTeethNoslipBase = 1; 
trackTeethNoslipTop = 3;

module track_basicring(r = 10) render(convexity = 3) {
	difference() {
		cylinder(r = r + trackThickness, h = trackWidth);
		translate([0, 0, -0.1]) cylinder(r = r, h = trackWidth + 0.2);
	}
}

module track_tooth() {
	teethOffset = $teeth_use_offset ? playLooseFit : 0;

	trackTeethBaseWidth = trackTeethBaseWidth + teethOffset * 2;
	trackTeethTopWidth = trackTeethTopWidth + teethOffset * 2;
	trackTeethHeight = trackTeethHeight + teethOffset;

	linear_extrude(height = trackWidth) {
		polygon([	[trackTeethBaseWidth/2, 0],
						[trackTeethTopWidth/2, -trackTeethHeight],
						[-trackTeethTopWidth/2, -trackTeethHeight],
						[-trackTeethBaseWidth/2, 0]]);
	}
}

module track_teeth_noslip(r = 10) {
	teethOffset = $teeth_use_offset ? playLooseFit : 0;

	trackTeethHeight = trackTeethHeight + teethOffset;

	rotate_extrude() {
		polygon([	[r - trackTeethHeight - 0.01, trackTeethNoslipTop/2],
						[r - trackTeethHeight - 0.01, -trackTeethNoslipTop/2],
						[r + 0.01, -trackTeethNoslipBase/2],
						[r + 0.01, trackTeethNoslipBase/2]]);
	}
}

module track_teeth(r = 10, tRadius = -1) {
	tRadius = (tRadius < 0) ? r : tRadius;
	
	trackCircumference = 6.28318 * tRadius;
	teethNum = floor(trackCircumference / trackTeethSpacing);

	intersection() {
		for(i=[0:360/teethNum:360]) rotate([0, 0, i]) render() difference() {
			translate([0, r, 0]) track_tooth();
			translate([0, 0, trackWidth/2]) track_teeth_noslip(r);
		}

		cylinder(r = r + 0.001, h = trackWidth);
	}
}

module track(r = 10, rShrink = 0, clearance_offset = false) {
	$teeth_use_offset = clearance_offset;

	track_teeth(r - rShrink, r);
	track_basicring(r - rShrink);
}

module basic_wheel() render(convexity = 3) {
	difference() {
		cylinder(r = wheelSize, h = trackWidth);
		track(r = wheelSize, clearance_offset = true);
	}
}

module motor_axis() {
	difference() {
		cylinder(d = 5, h = 100);
		translate([2, -5, 0]) cube([5, 10, 100]);
	}
}
	
module motor_wheel() {
	difference() {
		basic_wheel(); 
		translate([0,0, -0.1]) motor_axis();
	}
}

module slipring_wheel() {
	difference() {
		union() {
			basic_wheel();
			translate([0, 0, trackWidth - 0.1]) cylinder(d = 11.5, h = 2);
		}
		translate([0, 0, -0.1]) cylinder(d = 8, h = 100);
		
		for(x = [-1, 1]) translate([x*7.5, 0, -0.1]) cylinder(d = 3, h = 100);
	}
}

track(r = wheelSize + (80)/6.28);
		

