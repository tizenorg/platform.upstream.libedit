Name:           libedit
Version:        3.1.snap20130712
Release:        0
%define pkg_name    libedit
%define pkg_version 20130712-3.1
Source:         %{name}-%{pkg_version}.tar.gz
Source2:        baselibs.conf
Summary:        Command Line Editing and History Library
License:        BSD-3-Clause
Group:          Development/Libraries
Url:            http://www.thrysoee.dk/editline/
BuildRequires:  gcc-c++
BuildRequires:  libtool
BuildRequires:  ncurses-devel
BuildRequires:  pkgconfig

%description
libedit is a command line editing and history library. It is designed
to be used by interactive programs that allow the user to type commands
at a terminal prompt.

%package devel
Requires:       %{name} = %{version}
Requires:       glibc-devel
Summary:        Development files for libedit

%description devel
libedit is a command line editing and history library. It is designed
to be used by interactive programs that allow the user to type commands
at a terminal prompt.

This package holds the development files for libedit.

%prep
%setup -q -n %{name}-%{pkg_version}

%build
NOCONFIGURE=1 autoreconf -fiv
%configure --disable-static --with-pic \
    --disable-silent-rules \
    --enable-widec

make %{?_smp_mflags}

%check
make check

%install
%make_install


%post   -p /sbin/ldconfig

%postun  -p /sbin/ldconfig

%files 
%defattr(-,root,root,-)
%{_libdir}/libedit.so.*
%{_mandir}/man5/editrc.5*
%license COPYING

%files -n libedit-devel
%defattr(-,root,root,-)
%{_libdir}/libedit.so
%{_includedir}/histedit.h
%{_includedir}/editline/
%{_mandir}/man3/*.3%{ext_man}
%{_libdir}/pkgconfig/libedit.pc

%changelog
