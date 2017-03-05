SRC_DIR = src
OUT_DIR = out

JFLAGS = -g -d $(OUT_DIR) -cp .:/usr/share/java/junit4.jar:$(OUT_DIR)
JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	  RegexValidator.java \
	  DomainValidator.java \
	  InetAddressValidator.java \
	  ResultPair.java \
	  UrlValidator.java \

CLASSES := $(CLASSES:%=$(SRC_DIR)/%)

CLASSES += test/UrlValidatorTest.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
