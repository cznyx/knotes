<?xml version="1.0" encoding="UTF-8"?>
<kcfg xmlns="http://www.kde.org/standards/kcfg/1.0"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.kde.org/standards/kcfg/1.0
      http://www.kde.org/standards/kcfg/1.0/kcfg.xsd" >
  <group name="Version">
     <entry name="NotesVersion" type="UInt">
        <default>0</default>
     </entry>
  </group>

  <group name="Printing">
     <entry name="Theme" type="String">
        <default>${DATA_INSTALL_DIR}/knotes/print/themes/default/</default>
     </entry>
  </group>

  <group name="Actions">
    <entry name="MailAction" type="String">
      <default>kmail --subject %t --body %f</default>
    </entry>
  </group>

  <group name="Alarms">
    <entry name="CheckInterval" type="UInt">
      <default>60</default>
    </entry>

    <entry name="AlarmsLastChecked" type="DateTime"/>
  </group>

  <group name="Network">
    <entry name="ReceiveNotes" type="Bool">
      <default>false</default>
    </entry>

    <entry name="Port" type="UInt">
      <label>The port KNotes will listen on and send notes to.</label>
      <default>24837</default>
    </entry>

    <entry name="SenderID" type="String"/>

    <entry name="KnownHosts" type="StringList"/>
    <entry name="NoteHostDialogSize" type="Size"/>
  </group>

</kcfg>