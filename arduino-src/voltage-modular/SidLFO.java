package com.goblin.sidlfo;


import voltage.controllers.*;
import voltage.core.*;
import voltage.core.Jack.JackType;
import voltage.sources.*;
import voltage.utility.*;
import voltage.processors.*;
import voltage.effects.*;
import java.awt.*;

//[user-imports]   Add your own imports here

import javax.sound.midi.ShortMessage;

import com.goblin.utils.*;

//[/user-imports]


public class SidLFO extends VoltageModule
//[user-inheritance]
//[/user-inheritance]
{

   public SidLFO( long moduleID, VoltageObjects voltageObjects )
   {
      super( moduleID, voltageObjects, "SidLFO", ModuleType.ModuleType_Utility, 1.4 );

      InitializeControls();


      canBeBypassed = false;
      SetSkin( "09e2ee366a7d450dbdc12bfdbb112181" );
   }

void InitializeControls()
{

      frequency = new VoltageKnob( "frequency", "frequency", this, 0.0, 127, 0 );
      AddComponent( frequency );
      frequency.SetWantsMouseNotifications( false );
      frequency.SetPosition( 9, 32 );
      frequency.SetSize( 27, 27 );
      frequency.SetSkin( "Plastic White" );
      frequency.SetRange( 0.0, 127, 0, false, 128 );
      frequency.SetKnobParams( 215, 145 );
      frequency.DisplayValueInPercent( false );
      frequency.SetKnobAdjustsRing( true );

      pwENV = new VoltageKnob( "pwENV", "pwENV", this, -63, 63, 0 );
      AddComponent( pwENV );
      pwENV.SetWantsMouseNotifications( false );
      pwENV.SetPosition( 10, 153 );
      pwENV.SetSize( 27, 27 );
      pwENV.SetSkin( "Plastic White" );
      pwENV.SetRange( -63, 63, 0, false, 127 );
      pwENV.SetKnobParams( 215, 145 );
      pwENV.DisplayValueInPercent( false );
      pwENV.SetKnobAdjustsRing( true );

      pitchENV = new VoltageKnob( "pitchENV", "pitchENV", this, -63, 63, 0 );
      AddComponent( pitchENV );
      pitchENV.SetWantsMouseNotifications( false );
      pitchENV.SetPosition( 54, 151 );
      pitchENV.SetSize( 27, 27 );
      pitchENV.SetSkin( "Plastic White" );
      pitchENV.SetRange( -63, 63, 0, false, 127 );
      pitchENV.SetKnobParams( 215, 145 );
      pitchENV.DisplayValueInPercent( false );
      pitchENV.SetKnobAdjustsRing( true );

      attack = new VoltageKnob( "attack", "attack", this, 0.0, 127, 0 );
      AddComponent( attack );
      attack.SetWantsMouseNotifications( false );
      attack.SetPosition( 57, 31 );
      attack.SetSize( 27, 27 );
      attack.SetSkin( "Plastic White" );
      attack.SetRange( 0.0, 127, 0, false, 128 );
      attack.SetKnobParams( 215, 145 );
      attack.DisplayValueInPercent( false );
      attack.SetKnobAdjustsRing( true );

      shape = new VoltageSwitch( "shape", "shape", this, 0 );
      AddComponent( shape );
      shape.SetWantsMouseNotifications( false );
      shape.SetPosition( 28, 216 );
      shape.SetSize( 39, 15 );
      shape.SetSkin( "3-State Slide Horizontal" );

      free = new VoltageToggle( "free", "free", this, false, 0 );
      AddComponent( free );
      free.SetWantsMouseNotifications( false );
      free.SetPosition( 7, 101 );
      free.SetSize( 33, 19 );
      free.SetSkin( "Short Green 2" );
      free.ShowOverlay( false );
      free.SetOverlayText( "" );

      textLabel1 = new VoltageLabel( "textLabel1", "textLabel1", this, "Freq" );
      AddComponent( textLabel1 );
      textLabel1.SetWantsMouseNotifications( false );
      textLabel1.SetPosition( 0, 56 );
      textLabel1.SetSize( 47, 30 );
      textLabel1.SetEditable( false, false );
      textLabel1.SetJustificationFlags( VoltageLabel.Justification.HorizCentered );
      textLabel1.SetJustificationFlags( VoltageLabel.Justification.VertCentered );
      textLabel1.SetColor( new Color( 255, 255, 255, 255 ) );
      textLabel1.SetBkColor( new Color( 65, 65, 65, 0 ) );
      textLabel1.SetBorderColor( new Color( 0, 0, 0, 0 ) );
      textLabel1.SetBorderSize( 1 );
      textLabel1.SetMultiLineEdit( false );
      textLabel1.SetIsNumberEditor( false );
      textLabel1.SetNumberEditorRange( 0, 100 );
      textLabel1.SetNumberEditorInterval( 1 );
      textLabel1.SetNumberEditorUsesMouseWheel( false );
      textLabel1.SetHasCustomTextHoverColor( false );
      textLabel1.SetTextHoverColor( new Color( 0, 0, 0, 255 ) );
      textLabel1.SetFont( "<Sans-Serif>", 14, false, false );

      textLabel2 = new VoltageLabel( "textLabel2", "textLabel2", this, "Attack" );
      AddComponent( textLabel2 );
      textLabel2.SetWantsMouseNotifications( false );
      textLabel2.SetPosition( 44, 55 );
      textLabel2.SetSize( 51, 30 );
      textLabel2.SetEditable( false, false );
      textLabel2.SetJustificationFlags( VoltageLabel.Justification.HorizCentered );
      textLabel2.SetJustificationFlags( VoltageLabel.Justification.VertCentered );
      textLabel2.SetColor( new Color( 255, 255, 255, 255 ) );
      textLabel2.SetBkColor( new Color( 65, 65, 65, 0 ) );
      textLabel2.SetBorderColor( new Color( 0, 0, 0, 0 ) );
      textLabel2.SetBorderSize( 1 );
      textLabel2.SetMultiLineEdit( false );
      textLabel2.SetIsNumberEditor( false );
      textLabel2.SetNumberEditorRange( 0, 100 );
      textLabel2.SetNumberEditorInterval( 1 );
      textLabel2.SetNumberEditorUsesMouseWheel( false );
      textLabel2.SetHasCustomTextHoverColor( false );
      textLabel2.SetTextHoverColor( new Color( 0, 0, 0, 255 ) );
      textLabel2.SetFont( "<Sans-Serif>", 14, false, false );

      textLabel3 = new VoltageLabel( "textLabel3", "textLabel3", this, "Free" );
      AddComponent( textLabel3 );
      textLabel3.SetWantsMouseNotifications( false );
      textLabel3.SetPosition( 1, 122 );
      textLabel3.SetSize( 44, 30 );
      textLabel3.SetEditable( false, false );
      textLabel3.SetJustificationFlags( VoltageLabel.Justification.HorizCentered );
      textLabel3.SetJustificationFlags( VoltageLabel.Justification.VertCentered );
      textLabel3.SetColor( new Color( 255, 255, 255, 255 ) );
      textLabel3.SetBkColor( new Color( 65, 65, 65, 0 ) );
      textLabel3.SetBorderColor( new Color( 0, 0, 0, 0 ) );
      textLabel3.SetBorderSize( 1 );
      textLabel3.SetMultiLineEdit( false );
      textLabel3.SetIsNumberEditor( false );
      textLabel3.SetNumberEditorRange( 0, 100 );
      textLabel3.SetNumberEditorInterval( 1 );
      textLabel3.SetNumberEditorUsesMouseWheel( false );
      textLabel3.SetHasCustomTextHoverColor( false );
      textLabel3.SetTextHoverColor( new Color( 0, 0, 0, 255 ) );
      textLabel3.SetFont( "<Sans-Serif>", 14, false, false );

      textLabel4 = new VoltageLabel( "textLabel4", "textLabel4", this, "Pitch" );
      AddComponent( textLabel4 );
      textLabel4.SetWantsMouseNotifications( false );
      textLabel4.SetPosition( 44, 179 );
      textLabel4.SetSize( 50, 30 );
      textLabel4.SetEditable( false, false );
      textLabel4.SetJustificationFlags( VoltageLabel.Justification.HorizCentered );
      textLabel4.SetJustificationFlags( VoltageLabel.Justification.VertCentered );
      textLabel4.SetColor( new Color( 255, 255, 255, 255 ) );
      textLabel4.SetBkColor( new Color( 65, 65, 65, 0 ) );
      textLabel4.SetBorderColor( new Color( 0, 0, 0, 0 ) );
      textLabel4.SetBorderSize( 1 );
      textLabel4.SetMultiLineEdit( false );
      textLabel4.SetIsNumberEditor( false );
      textLabel4.SetNumberEditorRange( 0, 100 );
      textLabel4.SetNumberEditorInterval( 1 );
      textLabel4.SetNumberEditorUsesMouseWheel( false );
      textLabel4.SetHasCustomTextHoverColor( false );
      textLabel4.SetTextHoverColor( new Color( 0, 0, 0, 255 ) );
      textLabel4.SetFont( "<Sans-Serif>", 14, false, false );

      textLabel5 = new VoltageLabel( "textLabel5", "textLabel5", this, "PW" );
      AddComponent( textLabel5 );
      textLabel5.SetWantsMouseNotifications( false );
      textLabel5.SetPosition( 3, 179 );
      textLabel5.SetSize( 40, 30 );
      textLabel5.SetEditable( false, false );
      textLabel5.SetJustificationFlags( VoltageLabel.Justification.HorizCentered );
      textLabel5.SetJustificationFlags( VoltageLabel.Justification.VertCentered );
      textLabel5.SetColor( new Color( 255, 255, 255, 255 ) );
      textLabel5.SetBkColor( new Color( 65, 65, 65, 0 ) );
      textLabel5.SetBorderColor( new Color( 0, 0, 0, 0 ) );
      textLabel5.SetBorderSize( 1 );
      textLabel5.SetMultiLineEdit( false );
      textLabel5.SetIsNumberEditor( false );
      textLabel5.SetNumberEditorRange( 0, 100 );
      textLabel5.SetNumberEditorInterval( 1 );
      textLabel5.SetNumberEditorUsesMouseWheel( false );
      textLabel5.SetHasCustomTextHoverColor( false );
      textLabel5.SetTextHoverColor( new Color( 0, 0, 0, 255 ) );
      textLabel5.SetFont( "<Sans-Serif>", 14, false, false );

      textLabel6 = new VoltageLabel( "textLabel6", "textLabel6", this, "LFO" );
      AddComponent( textLabel6 );
      textLabel6.SetWantsMouseNotifications( false );
      textLabel6.SetPosition( 0, 0 );
      textLabel6.SetSize( 72, 30 );
      textLabel6.SetEditable( false, false );
      textLabel6.SetJustificationFlags( VoltageLabel.Justification.HorizCentered );
      textLabel6.SetJustificationFlags( VoltageLabel.Justification.VertCentered );
      textLabel6.SetColor( new Color( 255, 255, 255, 255 ) );
      textLabel6.SetBkColor( new Color( 65, 65, 65, 0 ) );
      textLabel6.SetBorderColor( new Color( 0, 0, 0, 0 ) );
      textLabel6.SetBorderSize( 1 );
      textLabel6.SetMultiLineEdit( false );
      textLabel6.SetIsNumberEditor( false );
      textLabel6.SetNumberEditorRange( 0, 100 );
      textLabel6.SetNumberEditorInterval( 1 );
      textLabel6.SetNumberEditorUsesMouseWheel( false );
      textLabel6.SetHasCustomTextHoverColor( false );
      textLabel6.SetTextHoverColor( new Color( 0, 0, 0, 255 ) );
      textLabel6.SetFont( "<Sans-Serif>", 14, true, false );

      midiOut = new VoltageMidiJack( "midiOut", "midiOut", this, JackType.JackType_MidiOutput );
      AddComponent( midiOut );
      midiOut.SetWantsMouseNotifications( false );
      midiOut.SetPosition( 28, 305 );
      midiOut.SetSize( 37, 37 );
      midiOut.SetSkin( "Mini MIDI Jack" );
}



   //-------------------------------------------------------------------------------
   //  public void Initialize()

      //  Initialize will get called shortly after your module's constructor runs. You can use it to
      //  do any initialization that the auto-generated code doesn't handle.
   //-------------------------------------------------------------------------------
   @Override
   public void Initialize()
   {
      //[user-Initialize]   Add your own initialization code here



      //[/user-Initialize]
   }


   //-------------------------------------------------------------------------------
   //  public void Destroy()

      //  Destroy will get called just before your module gets deleted. You can use it to perform any
      //  cleanup that's not handled automatically by Java.
   //-------------------------------------------------------------------------------
   @Override
   public void Destroy()
   {
      super.Destroy();
      //[user-Destroy]   Add your own module-getting-deleted code here



      //[/user-Destroy]
   }


   //-------------------------------------------------------------------------------
   //  public boolean Notify( VoltageComponent component, ModuleNotifications notification, double doubleValue, long longValue, int x, int y, Object object )

      //  Notify will get called when various events occur - control values changing, timers firing, etc.
   //-------------------------------------------------------------------------------
   @Override
   public boolean Notify( VoltageComponent component, ModuleNotifications notification, double doubleValue, long longValue, int x, int y, Object object )
   {
      //[user-Notify]   Add your own notification handling code between this line and the notify-close comment
      switch( notification )
      {
         case Knob_Changed:   // doubleValue is the new VoltageKnob value
         {
            send();
         }
         break;
      
         case Slider_Changed:   // doubleValue is the new slider value
         {
         }
         break;
      
         case Button_Changed:   // doubleValue is the new button/toggle button value
         {
            send();
         }
         break;
      
         case Switch_Changed:   // doubleValue is the new switch value
         {
            send();
         }
         break;
      
         case Jack_Connected:   // longValue is the new cable ID
         {
            send();
         }
         break;
      
         case Jack_Disconnected:   // All cables have been disconnected from this jack
         {
         }
         break;
      
         case GUI_Update_Timer:   // Called every 50ms (by default) if turned on
         {
         }
         break;
      
         case Object_MouseMove:   // called when mouse is over an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_MouseLeave:  // called when mouse leaves an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_LeftButtonDown:   // called when user left-clicks on an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_LeftButtonUp:   // called when user releases left mouse button on an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_RightButtonDown:   // called when user releases right mouse button on an object that receives mouse notifications. 'object' parameter is a VoltageMouseKeyFlags object.
         {
         }
         break;
      
         case Object_RightButtonUp:   // called when user right-clicks on an object that receives mouse notifications
         {
         }
         break;
      
         case Object_LeftButtonDoubleClick: // called when user left-button double-clicks on an object that receives mouse notifications
         {
         }
         break;
      
         // Less common notifications:
      
         case Named_Timer:   // object contains a String with the name of the timer that has fired
         {
         }
         break;
      
         case Canvas_Painting:   // About to paint canvas.  object is a java.awt.Rectangle with painting boundaries
         {
         }
         break;
      
         case Canvas_Painted:   // Canvas painting is complete
         {
         }
         break;
      
         case Control_DragStart:    // A user has started dragging on a control that has been marked as draggable
         {
         }
         break;
      
         case Control_DragOn:       // This control has been dragged over during a drag operation. object contains the dragged object
         {
         }
         break;
      
         case Control_DragOff:      // This control has been dragged over during a drag operation. object contains the dragged object
         {
         }
         break;
      
         case Control_DragEnd:      // A user has ended their drag on a control that has been marked as draggable
         {
         }
         break;
      
         case Label_Changed:        // The text of an editable text control has changed
         {
         }
         break;
      
         case SoundPlayback_Start:   // A sound has begun playback
         {
            send();
         }
         break;
      
         case SoundPlayback_End:     // A sound has ended playback
         {
         }
         break;
      
         case Scrollbar_Position:    // longValue is the new scrollbar position
         {
         }
         break;
      
         case PolyVoices_Changed:    // longValue is the new number of poly voices
         {
         }
         break;
      
         case File_Dropped:     // 'object' is a String containing the file path
         {
         }
         break;
      
         case Preset_Loading_Start:   // called when preset loading begins
         {
         }
         break;
      
         case Preset_Loading_Finish:  // called when preset loading finishes
         {
         }
         break;
      
         case Variation_Loading_Start:    // sent when a variation is about to load
         {
         }
         break;
      
         case Variation_Loading_Finish:   // sent when a variation has just finished loading
         {
         }
         break;
      
         case Tempo_Changed:     // doubleValue is the new tempo
         {
         }
         break;
      
         case Randomized:     // called when the module's controls get randomized
         {
         }
         break;
      
         case VariationListChanged:   // sent when a variation gets added, deleted, or renamed, or the variations list gets reordered
         {
         }
         break;
      
         case Key_Press:     // sent when module has keyboard focus and a key is pressed; object is a VoltageKeyPressInfo object
         {
         }
         break;
      
         case Reset:    // sent when the module has been reset to default settings
         {
            send();
         }
         break;
      
         case Keyboard_NoteOn:   // sent when a note has been pressed on a VoltageKeyboard object. longValue is the note value ( 0-127 )
         {
         }
         break;
      
         case Keyboard_NoteOff:   // sent when a note has been released on a VoltageKeyboard object. longValue is the note value ( 0-127 )
         {
         }
         break;
      
         case Curve_Changed:   // sent when user has edited a curve's value. 'object' will be a VoltageCurve.CurveChangeNotification object.
         {
         }
         break;
      }



      return false;
      //[/user-Notify]
   }


   //-------------------------------------------------------------------------------
   //  public void ProcessSample()

      //  ProcessSample is called once per sample. Usually it's where you read
      //  from input jacks, process audio, and write it to your output jacks.
      //  Since ProcesssSample gets called 48,000 times per second, offload CPU-intensive operations
      //  to other threads when possible and avoid calling native functions.
   //-------------------------------------------------------------------------------
   @Override
   public void ProcessSample()
   {
      //[user-ProcessSample]   Add your own process-sampling code here

      if (sent) {
         return;
      }

      long currentTime = System.currentTimeMillis();
      
      if (currentTime - startTime >= 2500) {
         send();
         sent = true;
      }

      //[/user-ProcessSample]
   }


   //-------------------------------------------------------------------------------
   //  public String GetTooltipText( VoltageComponent component )

      //  Gets called when a tooltip is about to display for a control. Override it if
      //  you want to change what the tooltip displays - if you want a knob to work in logarithmic fashion,
      //  for instance, you can translate the knob's current value to a log-based string and display it here.
   //-------------------------------------------------------------------------------
   @Override
   public String GetTooltipText( VoltageComponent component )
   {
      //[user-GetTooltipText]   Add your own code here



      return super.GetTooltipText( component );
      //[/user-GetTooltipText]
   }


   //-------------------------------------------------------------------------------
   //  public void EditComponentValue( VoltageComponent component, double newValue, String newText )

      //  Gets called after a user clicks on a tooltip and types in a new value for a control. Override this if
      //  you've changed the default tooltip display (translating a linear value to logarithmic, for instance)
      //  in GetTooltipText().
   //-------------------------------------------------------------------------------
   @Override
   public void EditComponentValue( VoltageComponent component, double newValue, String newText )
   {
      //[user-EditComponentValue]   Add your own code here



      //[/user-EditComponentValue]
      super.EditComponentValue( component, newValue, newText );
   }


   //-------------------------------------------------------------------------------
   //  public void OnUndoRedo( String undoType, double newValue, Object optionalObject )

      //  If you've created custom undo events via calls to CreateUndoEvent, you'll need to
      //  process them in this function when they get triggered by undo/redo actions.
   //-------------------------------------------------------------------------------
   @Override
   public void OnUndoRedo( String undoType, double newValue, Object optionalObject )
   {
      //[user-OnUndoRedo]   Add your own code here



      //[/user-OnUndoRedo]
   }


   //-------------------------------------------------------------------------------
   //  public byte[] GetStateInformation()

      //  Gets called when the module's state gets saved, typically when the user saves a preset with
      //  this module in it. Voltage Modular will automatically save the states of knobs, sliders, etc.,
      //  but if you have any custom state information you need to save, return it from this function.
   //-------------------------------------------------------------------------------
   @Override
   public byte[] GetStateInformation()
   {
      //[user-GetStateInformation]   Add your own code here



      return null;
      //[/user-GetStateInformation]
   }


   //-------------------------------------------------------------------------------
   //  public void SetStateInformation(byte[] stateInfo)

      //  Gets called when this module's state is getting restored, typically when a user opens a preset with
      //  this module in it. The stateInfo parameter will contain whatever custom data you stored in GetStateInformation().
   //-------------------------------------------------------------------------------
   @Override
   public void SetStateInformation(byte[] stateInfo)
   {
      //[user-SetStateInformation]   Add your own code here

      send();

      //[/user-SetStateInformation]
   }


   //-------------------------------------------------------------------------------
   //  public byte[] GetStateInformationForVariations()

      //  Gets called when a user saves a variation with this module in it.
      //  Voltage Modular will automatically save the states of knobs, sliders, etc.,
      //  but if you have any custom state information you need to save, return it from this function.
   //-------------------------------------------------------------------------------
   @Override
   public byte[] GetStateInformationForVariations()
   {
      //[user-GetStateInformationForVariations]   Add your own code here



      return GetStateInformation();
      //[/user-GetStateInformationForVariations]
   }


   //-------------------------------------------------------------------------------
   //  public void SetStateInformationForVariations(byte[] stateInfo)

      //  Gets called when a user loads a variation with this module in it.
      //  The stateInfo parameter will contain whatever custom data you stored in GetStateInformationForVariations().
   //-------------------------------------------------------------------------------
   @Override
   public void SetStateInformationForVariations(byte[] stateInfo)
   {
      //[user-SetStateInformationForVariations]   Add your own code here
      SetStateInformation(stateInfo);



      //[/user-SetStateInformationForVariations]
   }


   // Auto-generated variables
   private VoltageMidiJack midiOut;
   private VoltageLabel textLabel6;
   private VoltageLabel textLabel5;
   private VoltageLabel textLabel4;
   private VoltageLabel textLabel3;
   private VoltageLabel textLabel2;
   private VoltageLabel textLabel1;
   private VoltageToggle free;
   private VoltageSwitch shape;
   private VoltageKnob attack;
   private VoltageKnob pitchENV;
   private VoltageKnob pwENV;
   private VoltageKnob frequency;


   //[user-code-and-variables]    Add your own variables and functions here

   private void sendCCMessage(byte cc, int value) {
      try {
         ShortMessage m = new ShortMessage();
         m.setMessage(ShortMessage.CONTROL_CHANGE, cc, value);
         midiOut.AddMessage(m);
      } catch (Exception e) {}
   }

   private void send() {
      if (pitchENV.GetValue() != 0) {
         sendPitch();
      } else {
         sendCCMessage(SidConstants.CC_PITCH_LFO_ENV, 63);
      }
      
      if (pwENV.GetValue() != 0) {
         sendPW();
      } else {
         sendCCMessage(SidConstants.CC_PW_LFO_ENV, 63);      
      }
   }

   private void sendPitch() {
      sendCCMessage(SidConstants.CC_PITCH_LFO_FREQ, (int)frequency.GetValue());
      sendCCMessage(SidConstants.CC_PITCH_LFO_ATTACK, (int)attack.GetValue());
      sendCCMessage(SidConstants.CC_PITCH_LFO_FREE, (int)free.GetValue());
      sendCCMessage(SidConstants.CC_PITCH_LFO_SHAPE, (int)shape.GetValue());
      sendCCMessage(SidConstants.CC_PITCH_LFO_ENV, (int)(pitchENV.GetValue() + 63.0));

   }

   private void sendPW() {
      sendCCMessage(SidConstants.CC_PW_LFO_FREQ, (int)frequency.GetValue());
      sendCCMessage(SidConstants.CC_PW_LFO_ATTACK, (int)attack.GetValue());
      sendCCMessage(SidConstants.CC_PW_LFO_FREE, (int)free.GetValue());
      sendCCMessage(SidConstants.CC_PW_LFO_SHAPE, (int)shape.GetValue());
      sendCCMessage(SidConstants.CC_PW_LFO_ENV, (int)(pwENV.GetValue() + 63.0));   
   }

   private long startTime = System.currentTimeMillis();
   private boolean sent = false;

   //[/user-code-and-variables]
}

 