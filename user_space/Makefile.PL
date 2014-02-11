#!/usr/bin/perl -w
#    GNU Public License (GPL)
#
#    Copyright (c) 2008 Stéphane GALLAND <galland@arakhne.org>
#
#    This program is free software; you can redistribute it and/or modify it
#    under the terms of the GNU General Public License as published by the
#    Free Software Foundation; either version 2 of the License, or (at your
#    option) any later version.
#
#    This program is distributed in the hope that it will be useful, but
#    WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
#    Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this program; see the file COPYING. If not, write to the Free
#    Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
#    02111-1307, USA.

use strict;

use File::Basename;
use File::Copy;
use File::Spec;
use File::Path;
use Pod::Man;
use Compress::Zlib;

my %dirs;

sub filename(@) {
	return File::Spec->catfile(@_);
}
sub mkdirP(@) {
	for my $p (@_) {
		my @path = File::Spec->splitdir("$p");
		my $rp = '';

		if (!$path[0]) {
			shift @path;
		}
		else {
			$rp = '.';
		}

		for my $a (@path) {
			$a = '.' unless ($a);
			$rp = File::Spec->catfile("$rp","$a");
			if (! -d "$rp") {
				mkdir("$rp") or die("mkdirP: $rp: $!\n");
			}
		}
	}
	return 1;
}
sub replace($$@) {
	my $in = shift;
	my $out = shift;
	local *INF;
	local *OUTF;
	open(*INF, "< $in") or die("replace: $in: $!\n");
	open(*OUTF, "> $out") or die("replace: $out: $!\n");
	while (my $line = <INF>) {
		for(my $i=0; $i<@_; $i+=2) {
			my $source = $_[$i];
			my $replacement = $_[$i+1];
			$line =~ s/\Q$source\E/$replacement/g;
		}
		print OUTF "$line";
	}
	close(*OUTF);
	close(*INF);
	return 1;
}
sub readFile($) {
	my $filename = shift;
	local *IN;
	open(*IN, "< $filename") or die("readFile: $filename: $!\n");
	my $line = <IN>;
	close(*IN);
	$line = '' unless ($line);
	$line =~ s/^\s+//;
	$line =~ s/\s+$//;
	return $line;
}
sub removePrefix($) {
	my $filename = shift;
	return $filename unless ($filename);
	return $filename unless ($dirs{'PREFIX'});
	my $prefix = File::Spec->rel2abs($dirs{'PREFIX'});
	$filename = File::Spec->rel2abs("$filename");
	$filename =~ s/^\Q$prefix\E//;
	return $filename;
}
sub gzipfct($) {
	my $targetfile = shift;
	local *IN;
	my $gz = gzopen("$targetfile.gz","wb") or die("$targetfile.gz: $!");
	open(*IN, "<", "$targetfile") or die("$targetfile: $!");
	while (<IN>) {
		$gz->gzwrite($_);
	}
	close(*IN);
	$gz->gzclose();
	unlink "$targetfile";
}
sub buildManual($$$$) {
	my $source = shift;
	my $target = shift;
	my $version = shift;
	my $section = shift;
	my $man_parser = Pod::Man->new('release'=>$version, section => $section);
	$man_parser->parse_from_file("$source","$target.$section");
	gzipfct("$target.$section");	
	print "\tbuilding manual into $target.$section.gz\n";
}
sub install($\%) {
	my $rights = shift;
	while (my ($file,$target) = each(%{$_[0]})) {
		if (-f "$file") {
			my $targetfile = filename("$target",basename("$file"));
			print "\t$file -> $targetfile\n";
			mkdirP("$target");
			copy("$file", "$targetfile")
				or die("can't install $file: $!\n");
			chmod($rights,"$targetfile")
				or die("can't change rights on $targetfile: $!\n");
		}
		else {
			die("can't install $file: $!\n");
		}
	}
}
sub installfile($@) {
	my $source = shift;
	my %toinstall = ();
	for(my $i=0; $i<@_; $i+=2) {
		$toinstall{filename("$source",$_[$i])} = $_[($i+1)];
	}
	install(0644,%toinstall);
}
sub installexec($@) {
	my $source = shift;
	my %toinstall = ();
	for(my $i=0; $i<@_; $i+=2) {
		$toinstall{filename("$source",$_[$i])} = $_[($i+1)];
	}
	install(0755,%toinstall);
}
sub installman($$$@) {
	my $source = shift;
	my $section = shift || 1;
	my $locale = shift || '';
	my $path;
	if ($locale) {
		$path = filename($dirs{'man'}, $locale, "man$section");
	}
	else {
		$path = filename($dirs{'man'}, "man$section");
	}
	my %toinstall = ();
	for my $p (@_) {
		$toinstall{filename("$source","$p")} = "$path";
	}
	install(0644,%toinstall);
}

# Default values
%dirs = (
	'bin' => filename('','usr','bin'),
	'sbin' => filename('','usr','sbin'),
	'etc' => filename('','etc'),
	'pixmaps' => filename('','usr','share','pixmaps'),
	'desktop' => filename('','usr','share','applications'),
	'man' => filename('','usr','share','man'),
	'tmp' => filename('','tmp'),
	'varrun' => filename('','var','run'),
	);

use constant TOP_DIR => dirname("$0");
use constant BUILD_DIR => filename(TOP_DIR,'build');
use constant SRC_DIR => filename(TOP_DIR,'src');
use constant IMG_DIR => filename(TOP_DIR,'img');
use constant MAN_DIR => filename(TOP_DIR,'man');
use constant DESKTOP_DIR => filename(TOP_DIR,'desktop');
use constant TRUE => 1;
use constant FALSE => 0;

#----------------------------------------------------------

my %actions = (
	'build' => {	'deps' => [],
			'done' => \&isBuilt,
			'run' => \&runBuild },
	'install' => {	'deps' => [ 'build' ],
			'done' => undef,
			'run' => \&runInstall },
	'clean' => {	'deps' => [],
			'done' => undef,
			'run' => \&runClean },
	);

sub isBuilt() {
	return (-f filename(BUILD_DIR,'3dxactivator'));
}

sub runBuild() {
	my @filetotreat = ('3dxactivator','3dxmanager','g3dxapplet');
	my @mantotreat = ('3dxactivator.pod','3dxmanager.pod','g3dxapplet.pod','3dxware.pod');

	mkdirP(BUILD_DIR);

	my $version = readFile(filename(TOP_DIR,'VERSION'));

	for my $file (@filetotreat) {
		replace(filename(SRC_DIR,"$file"),
			filename(BUILD_DIR,"$file"),
			'<<VERSION_NUMBER>>', "$version",
			'<<RUNNING_DIR>>', removePrefix(filename($dirs{'varrun'},'3dxware')),
			'<<3DXSRV_BINARY>>', removePrefix(filename($dirs{'sbin'},'3dxsrv')),
			'<<3DXMANAGER_BINARY>>', removePrefix(filename($dirs{'bin'},'3dxmanager')),
			'<<PIXMAPS_DIR>>', removePrefix($dirs{'pixmaps'}));
	}

	for my $file (@mantotreat) {
		buildManual(
			filename(MAN_DIR,"$file"),
			filename(BUILD_DIR,basename("$file",'.pod')),
			$version,
			1);
	}
}

sub runInstall() {
	installexec(BUILD_DIR,
			'3dxactivator' => $dirs{'sbin'},
			'3dxmanager' => $dirs{'bin'},
			'g3dxapplet' => $dirs{'bin'});
	installfile(IMG_DIR,
			'3dx.png' => $dirs{'pixmaps'},
			'3dx_off.png' => $dirs{'pixmaps'},
			'3dx_running.png' => $dirs{'pixmaps'},
			'3dx_stopped.png' => $dirs{'pixmaps'},
			'3dx_wait.png' => $dirs{'pixmaps'},
			'g3dx.png' => $dirs{'pixmaps'});
	installfile(DESKTOP_DIR,
			'3dxmanager_off.desktop' => $dirs{'desktop'},
			'3dxmanager_on.desktop' => $dirs{'desktop'},
			'g3dxapplet.desktop' => $dirs{'desktop'});
	installman(BUILD_DIR, 1, undef,
		'3dxware.1.gz', '3dxactivator.1.gz', '3dxmanager.1.gz', 'g3dxapplet.1.gz');
}

sub runClean() {
	rmtree(BUILD_DIR);
}


#----------------------------------------------------------

use Getopt::Long;

my $addPrefix = undef;

# Parse command line options
if (!GetOptions(
		'bin=s' => \$dirs{'bin'},
		'sbin=s' => \$dirs{'sbin'},
		'etc=s' => \$dirs{'etc'},
		'pixmaps=s' => \$dirs{'pixmaps'},
		'desktop=s' => \$dirs{'desktop'},
		'varrun=s' => \$dirs{'varrun'},
		'man=s' => \$dirs{'man'},
		'tmp=s' => \$dirs{'tmp'},
		'prefix=s' => \$dirs{'PREFIX'},
		'root=s' => \$addPrefix,
	)) {
	exit(1);
}

if ($addPrefix) {
	for my $k (keys %dirs) {
		my @p;
		if ($dirs{"$k"}) {
			@p = File::Spec->splitdir($dirs{"$k"});
		}
		else {
			@p = ('');
		}
		if (!$p[0]) {
			shift @p;
		}
		$dirs{"$k"} = filename("$addPrefix",@p);
	}
}

# Check command line action
my $do = FALSE;
for my $cmdaction (@ARGV) {
	if (exists $actions{"$cmdaction"}) {
		$do = TRUE;
		# Build the action list
		my @actiontoconsume = ("$cmdaction");
		my @actions = ();
		while (@actiontoconsume) {
			my $act = shift @actiontoconsume;
			push @actions, "$act";
			if ($actions{"$act"}{'deps'}) {
				push @actiontoconsume, @{$actions{"$act"}{'deps'}};
			}
		}
		@actions = reverse @actions;

		# Do the actions
		my %done = ();
		for my $act (@actions) {
			if (!$done{"$act"} && (!$actions{"$act"}{'done'} || !&{$actions{"$act"}{'done'}})) {
				print STDOUT "Running $act\n";
				if ($actions{"$act"}{'run'}) {
					&{$actions{"$act"}{'run'}};
				}
			}
			$done{"$act"} = TRUE;
		}
	}
}

die("nothing to do\n") unless ($do);

exit(0);

