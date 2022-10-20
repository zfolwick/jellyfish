# -*- encoding: utf-8 -*-
# stub: arduino_ci 1.3.0 ruby lib

Gem::Specification.new do |s|
  s.name = "arduino_ci".freeze
  s.version = "1.3.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0".freeze) if s.respond_to? :required_rubygems_version=
  s.require_paths = ["lib".freeze]
  s.authors = ["Ian Katz".freeze]
  s.bindir = "exe".freeze
  s.date = "2021-01-14"
  s.description = "".freeze
  s.email = ["arduino.continuous.integration@gmail.com".freeze]
  s.executables = ["arduino_ci.rb".freeze, "arduino_ci_remote.rb".freeze, "arduino_library_location.rb".freeze, "ensure_arduino_installation.rb".freeze]
  s.files = ["exe/arduino_ci.rb".freeze, "exe/arduino_ci_remote.rb".freeze, "exe/arduino_library_location.rb".freeze, "exe/ensure_arduino_installation.rb".freeze]
  s.homepage = "http://github.com/Arduino-CI/arduino_ci".freeze
  s.licenses = ["Apache-2.0".freeze]
  s.rubygems_version = "3.0.3.1".freeze
  s.summary = "Tools for building and unit testing Arduino libraries".freeze

  s.installed_by_version = "3.0.3.1" if s.respond_to? :installed_by_version

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<os>.freeze, ["~> 1.0"])
      s.add_runtime_dependency(%q<rubyzip>.freeze, ["~> 1.2"])
    else
      s.add_dependency(%q<os>.freeze, ["~> 1.0"])
      s.add_dependency(%q<rubyzip>.freeze, ["~> 1.2"])
    end
  else
    s.add_dependency(%q<os>.freeze, ["~> 1.0"])
    s.add_dependency(%q<rubyzip>.freeze, ["~> 1.2"])
  end
end
